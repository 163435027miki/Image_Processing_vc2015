#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//フォルダを作成する

using namespace cv;

char post_filename[128];
char post_derectroy[128];
char post_output[128];
char post_output_f[128];

int gradationN;

int posterization(char post_filename[], char date[]) {

	printf("ポスタリゼーションの諧調数\n");
	printf("256を割り切れない場合は白の諧調が落ちます\n");
	printf("gradation_number = ");
	scanf("%d", &gradationN);

	//入出力ファイルの指定
	sprintf(post_derectroy, "..\\Input_deta\\%s.bmp", post_filename);
	sprintf(post_output_f, "..\\output_deta\\%s", date);
	sprintf(post_output, "%s\\%s_post%d.bmp", post_output_f, post_filename, gradationN);

	//画像の読み込み
	cv::Mat ImputImage = cv::imread(post_derectroy);
	

	//画像サイズの取得
	int cols = ImputImage.cols;	//x
	int rows = ImputImage.rows;	//y

	//出力画像
	cv::Mat make_image = cv::Mat::zeros(rows, cols, CV_8UC1);

	
	std::vector<std::vector<int>>OutputRGB;
	std::vector<std::vector<int>>intensity;
	OutputRGB.resize(cols);
	intensity.resize(cols);
	for (int i = 0; i<cols; ++i) {
		OutputRGB[i].resize(rows);
		intensity[i].resize(rows);
	}
	
	/*
	std::vector<std::vector<int>>OutputRGB;
	std::vector<std::vector<int>>intensity;
	OutputRGB.resize(256);
	intensity.resize(256);
	for (int i = 0; i<256; ++i) {
		OutputRGB[i].resize(256);
		intensity[i].resize(256);
	}
	*/
	//画素値の取得
	for (int y = 0; y<rows; y++) {
		for (int x = 0; x<cols; x++) {
			//int a=3*x;
			//intensity[x][y] = srcImg.at<unsigned char>(y, a); //X座標がx, Y座標がyに位置するピクセルの値を取得
			//RGBの平均を画素値とする
			int B = ImputImage.at<Vec3b>(y, x)[0];
			int G = ImputImage.at<Vec3b>(y, x)[1];
			int R = ImputImage.at<Vec3b>(y, x)[2];
			intensity[x][y] = (R + B + G) / 3;
		}
	}
	
	double n1= ceil(float(256) / gradationN);
	int n =n1;//切り上げ
	printf("gradationN=%d\n", gradationN);
	
	printf("n=%d\n",n);

	//ポスタリゼーション処理
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			for (int k = 0; k < gradationN; ++k) {
				if (intensity[x][y] >= n*k && intensity[x][y] < n*(k + 1)) {
					OutputRGB[x][y] = n*k;
					make_image.at<uchar>(y, x) = OutputRGB[x][y];
				}

			}
		}
	}

	//outputを保存するディレクトリの作成
	if (_mkdir(post_output_f) == 0) {
		printf("フォルダ %s を作成しました\n", post_output_f);
	}
	else {
		printf("フォルダ作成に失敗しました。もしくは作成済みです\n");
	}
	
	//画像の保存
	imwrite(post_output, make_image);

	//名前をつける
	std::string windowName = "post_image";
	cv::namedWindow(windowName);

	//画面表示
	cv::imshow(windowName, make_image);

	cv::waitKey(0);
	
	return 0;

}