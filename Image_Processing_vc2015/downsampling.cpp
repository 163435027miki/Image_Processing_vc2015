#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//フォルダを作成する




char resize_filename[128];
char resize_derectroy[128];
char resize_output_NEAREST[128];
char resize_output_LINEAR[128];
char resize_output_CUBIC[128];
char resize_output_AREA[128];
char resize_output_LANCZOS4[128];
char resize_output_f[128];

char resize_derectroy_sd0[128];
char resize_derectroy_sd10[128];
char resize_derectroy_sd20[128];
char resize_derectroy_sd30[128];
char resize_derectroy_sd40[128];
char resize_derectroy_sd50[128];
char resize_output_sd0[128];
char resize_output_sd10[128];
char resize_output_sd20[128];
char resize_output_sd30[128];
char resize_output_sd40[128];
char resize_output_sd50[128];

int resizeN;

/*
int Downsampling(char resize_filename[], char date[]) {

	//入力ファイルの指定
	sprintf(resize_derectroy, "..\\Input_deta\\%s.bmp", resize_filename);

	//出力ファイルの設定
	sprintf(resize_output_f, "..\\output_deta\\%s", date);
	sprintf(resize_output_NEAREST, "%s\\%s_NEAREST.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_LINEAR, "%s\\%s_LINEAR.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_CUBIC, "%s\\%s_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_AREA, "%s\\%s_AREA.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_LANCZOS4, "%s\\%s_LANCZOS4.bmp", resize_output_f, resize_filename);

	printf("input : %s\n", resize_derectroy);


	//画像の読み込み
	cv::Mat srcImg = cv::imread(resize_derectroy);

	printf("変更するサイズの倍率を入力\n");
	printf("画像を 1/n 倍にする\n");
	printf("n= ");
	scanf("%d", &resizeN);

	//出力画像領域の確保
	cv::Mat dst_img1(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img2(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img3(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img4(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img5(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);

	//画像変形
	cv::resize(srcImg, dst_img1, dst_img1.size(), 1 / resizeN, 1 / resizeN, cv::INTER_NEAREST);			//ニアレストネイバー法
	cv::resize(srcImg, dst_img2, dst_img2.size(), 1 / resizeN, 1 / resizeN, cv::INTER_LINEAR);		//バイリニア法
	cv::resize(srcImg, dst_img3, dst_img3.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg, dst_img4, dst_img4.size(), 1 / resizeN, 1 / resizeN, cv::INTER_AREA);		//モアレを軽減させる
	cv::resize(srcImg, dst_img5, dst_img5.size(), 1 / resizeN, 1 / resizeN, cv::INTER_LANCZOS4);	//LANCZOSフィルタ

	//画像表示
	cv::namedWindow("NEAREST", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("LINEAR", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("CUBIC", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("AREA", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("LANCZOS4", cv::WINDOW_AUTOSIZE);
	cv::imshow("NEAREST", dst_img1);
	cv::imshow("LINEAR", dst_img2);
	cv::imshow("CUBIC", dst_img3);
	cv::imshow("AREA", dst_img4);
	cv::imshow("LANCZOS4", dst_img5);

	//outputを保存するディレクトリの作成
	if (_mkdir(resize_output_f) == 0) {
		printf("フォルダ %s を作成しました\n", resize_output_f);
	}
	else {
		printf("フォルダ作成に失敗しました。もしくは作成済みです\n");
		//waitKey(0);
	}

	//画像保存
	cv::imwrite(resize_output_NEAREST, dst_img1);
	cv::imwrite(resize_output_LINEAR, dst_img2);
	cv::imwrite(resize_output_CUBIC, dst_img3);
	cv::imwrite(resize_output_AREA, dst_img4);
	cv::imwrite(resize_output_LANCZOS4, dst_img5);

	//cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
*/

int Downsampling(char resize_filename[], char date[]) {

	

	//同じ手法でsd0~sd50までを処理する
	//入力ファイルの指定
	sprintf(resize_derectroy_sd0, "..\\Input_deta\\%s_sd0.bmp", resize_filename);
	sprintf(resize_derectroy_sd10, "..\\Input_deta\\%s_sd10.bmp", resize_filename);
	sprintf(resize_derectroy_sd20, "..\\Input_deta\\%s_sd20.bmp", resize_filename);
	sprintf(resize_derectroy_sd30, "..\\Input_deta\\%s_sd30.bmp", resize_filename);
	sprintf(resize_derectroy_sd40, "..\\Input_deta\\%s_sd40.bmp", resize_filename);
	sprintf(resize_derectroy_sd50, "..\\Input_deta\\%s_sd50.bmp", resize_filename);

	// 出力ファイルの設定
	sprintf(resize_output_f, "..\\output_deta\\%s", date);
	sprintf(resize_output_sd0, "%s\\%s_sd0_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_sd10, "%s\\%s_sd10_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_sd20, "%s\\%s_sd20_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_sd30, "%s\\%s_sd30_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_sd40, "%s\\%s_sd40_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_sd50, "%s\\%s_sd50_CUBIC.bmp", resize_output_f, resize_filename);
	

	printf("input : %s\n", resize_derectroy_sd0);
	printf("input : %s\n", resize_derectroy_sd10);
	printf("input : %s\n", resize_derectroy_sd20);
	printf("input : %s\n", resize_derectroy_sd30);
	printf("input : %s\n", resize_derectroy_sd40);
	printf("input : %s\n", resize_derectroy_sd50);




	//画像の読み込み
	cv::Mat srcImg_sd0 = cv::imread(resize_derectroy_sd0);
	cv::Mat srcImg_sd10 = cv::imread(resize_derectroy_sd10);
	cv::Mat srcImg_sd20 = cv::imread(resize_derectroy_sd20);
	cv::Mat srcImg_sd30 = cv::imread(resize_derectroy_sd30);
	cv::Mat srcImg_sd40 = cv::imread(resize_derectroy_sd40);
	cv::Mat srcImg_sd50 = cv::imread(resize_derectroy_sd50);

	printf("変更するサイズの倍率を入力\n");
	printf("画像を 1/n 倍にする\n");
	printf("n= ");
	scanf("%d", &resizeN);

	//出力画像領域の確保
	cv::Mat dst_img1(srcImg_sd0.rows / resizeN, srcImg_sd0.cols / resizeN, CV_8UC3);
	cv::Mat dst_img2(srcImg_sd10.rows / resizeN, srcImg_sd10.cols / resizeN, CV_8UC3);
	cv::Mat dst_img3(srcImg_sd20.rows / resizeN, srcImg_sd20.cols / resizeN, CV_8UC3);
	cv::Mat dst_img4(srcImg_sd30.rows / resizeN, srcImg_sd30.cols / resizeN, CV_8UC3);
	cv::Mat dst_img5(srcImg_sd40.rows / resizeN, srcImg_sd40.cols / resizeN, CV_8UC3);
	cv::Mat dst_img6(srcImg_sd50.rows / resizeN, srcImg_sd50.cols / resizeN, CV_8UC3);

	//画像変形
	cv::resize(srcImg_sd0, dst_img1, dst_img1.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg_sd10, dst_img2, dst_img2.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg_sd20, dst_img3, dst_img3.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg_sd30, dst_img4, dst_img4.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg_sd40, dst_img5, dst_img5.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法
	cv::resize(srcImg_sd50, dst_img6, dst_img6.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//キュービック法

																									//画像表示
	cv::namedWindow("sd0", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sd10", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sd20", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sd30", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sd40", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sd50", cv::WINDOW_AUTOSIZE);
	
	cv::imshow("sd0", dst_img1);
	cv::imshow("sd10", dst_img2);
	cv::imshow("sd20", dst_img3);
	cv::imshow("sd30", dst_img4);
	cv::imshow("sd40", dst_img5);
	cv::imshow("sd50", dst_img6);
	

	//outputを保存するディレクトリの作成
	if (_mkdir(resize_output_f) == 0) {
		printf("フォルダ %s を作成しました\n", resize_output_f);
	}
	else {
		printf("フォルダ作成に失敗しました。もしくは作成済みです\n");
		//waitKey(0);
	}

	//画像保存
	cv::imwrite(resize_output_sd0, dst_img1);
	cv::imwrite(resize_output_sd10, dst_img2);
	cv::imwrite(resize_output_sd20, dst_img3);
	cv::imwrite(resize_output_sd30, dst_img4);
	cv::imwrite(resize_output_sd40, dst_img5);
	cv::imwrite(resize_output_sd50, dst_img6);

	//cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
