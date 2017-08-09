#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//フォルダを作成する

char cut_filename[128];
char cut_derectroy[128];
char cut_output[128];
char cut_output_f[128];

int circle_cut(char cut_filename[], char date[]) {

	//半径から余白を設定する
	int margin = 5;

	//入出力ファイルの指定
	sprintf(cut_derectroy, "..\\Input_deta\\%s.bmp", cut_filename);
	sprintf(cut_output_f, "..\\output_deta\\%s", date);
	sprintf(cut_output, "%s\\%s_cut.bmp", cut_output_f, cut_filename);

	//画像の読み込み
	cv::Mat ImputImage = cv::imread(cut_derectroy);

	//画像サイズの取得
	int cols = ImputImage.cols;	//x
	int rows = ImputImage.rows;	//y

	int cols_center = cols / 2;
	int rows_center = rows / 2;
	

	int radius;
	if (cols >= rows) {
		radius = cols_center- margin;
	}
	else {
		radius = rows_center- margin;
	}


	//円をマスクとして描画
	cv::Mat circle = cv::Mat::zeros(cols, rows, CV_8UC3);
	cv::circle(circle, cv::Point(cols_center, rows_center), radius, cv::Scalar(255, 255, 255), -1, 8);
	
	//黒色背景の画像
	cv::Mat OutputImage = cv::Mat::zeros(cols, rows, CV_8UC3);

	//IplImage* src = cvLoadImage(cut_derectroy, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	//マスクの位置のみコピーする
	ImputImage.copyTo(OutputImage, circle);

	//outputを保存するディレクトリの作成
	if (_mkdir(cut_output_f) == 0) {
		printf("フォルダ %s を作成しました\n", cut_output_f);
	}
	else {
		printf("フォルダ作成に失敗しました。もしくは作成済みです\n");
	}

	
	//画像の保存
	imwrite(cut_output, OutputImage);

	//名前をつける
	std::string windowName = "cut_image";
	cv::namedWindow(windowName);

	//画面表示
	cv::imshow(windowName, OutputImage);

	cv::waitKey(0);

	return 0;

}