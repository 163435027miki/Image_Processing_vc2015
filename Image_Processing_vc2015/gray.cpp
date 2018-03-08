#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//フォルダを作成する

char inputgray_directory[120] = "..\\Input_deta\\";							//inputimageの場所
char outputgray_directory[120] = "..\\output_deta\\";						//outputiamgeの場所


char Output_gray_name[255];
char Input_gray_name[255];						//入力ファイル名・入力元の設定




char gray_filename[128];
char gray_derectroy[128];
char gray_output[128];
char gray_output_f[128];


using namespace std;
using namespace cv;

int gray_scale(char gray_filename[], char date[]) {

	for (int i = 1; i <= 45; ++i) {

		//入出力ファイルの指定
//		sprintf(Input_gray_name, "%s%s.bmp", inputgray_directory, gray_filename);
//		sprintf(gray_output_f, "%s%s", outputgray_directory, date);
//		sprintf(Output_gray_name, "%s\\%s.bmp", gray_output_f, gray_filename);

//入出力ファイルの指定
		sprintf(Input_gray_name, "%s%d.bmp", inputgray_directory, i);
		sprintf(gray_output_f, "%s%s", outputgray_directory, date);
		sprintf(Output_gray_name, "%s\\%d.bmp", gray_output_f, i);

		//画像の読み込み
		cv::Mat ImputImage = cv::imread(Input_gray_name);

		//出力画像を入れる場所
		cv::Mat gray_image;

		//outputを保存するディレクトリの作成
		if (_mkdir(gray_output_f) == 0) {
			printf("フォルダ %s を作成しました\n", gray_output_f);
		}
		else { printf("フォルダ作成に失敗しました。もしくは作成済みです\n"); }

		//グレースケール化
		cvtColor(ImputImage, gray_image, CV_RGB2GRAY);
/*
		//名前をつける
		std::string windowName = "image";
		cv::namedWindow(windowName);

		//画面表示
		cv::imshow(windowName, gray_image);

		//画像の保存
		imwrite(Output_gray_name, gray_image);

		cv::waitKey(0);
		*/
		//画像の保存
		imwrite(Output_gray_name, gray_image);
	}
	return 0;
}