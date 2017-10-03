#include <opencv2/opencv.hpp>
#include<math.h>
#include <string>
#include<sstream> //文字ストリーム
#include <direct.h>//フォルダを作成する



using namespace cv;
		int intensity[513][513];//出力結果を格納
		FILE *fp;
		

	char input[128];

	char fname[128];

	char gaso_filename[128];
	char gaso_derectroy[128];
	char gaso_output[128];
	char gaso_output_f[128];

int gaso(char gaso_filename[],char date[])
{
	
	//入出力ファイルの指定
	sprintf(gaso_derectroy,"..\\Input_deta\\%s.bmp",gaso_filename);
	sprintf(gaso_output_f,"..\\output_deta\\%s",date);
	sprintf(gaso_output,"%s\\%s.csv",gaso_output_f,gaso_filename);

	printf("input : %s\n",gaso_derectroy);
	printf("output : %s\n",gaso_output);
	
	//画像の読み込み
	cv::Mat srcImg = cv::imread(gaso_derectroy);

	//画像サイズの取得
	int cols=srcImg.cols;
	int rows=srcImg.rows;

	//画素値の取得
	for(int y=0;y<rows;y++){
		for(int x=0;x<cols;x++){
			//int a=3*x;
				//intensity[x][y] = srcImg.at<unsigned char>(y, a); //X座標がx, Y座標がyに位置するピクセルの値を取得

			//RGBの平均を画素値とする
				int B = srcImg.at<Vec3b>(y, x)[0];
				int G = srcImg.at<Vec3b>(y, x)[1];
				int R = srcImg.at<Vec3b>(y, x)[2];
				intensity[x][y]=(R+B+G)/3;
		}
	}

    //waitKey(0);

	//outputを保存するディレクトリの作成
	if (_mkdir(gaso_output_f) == 0) {
		printf("フォルダ %s を作成しました\n", gaso_output_f);
	}
	else {
		printf("フォルダ作成に失敗しました。もしくは作成済みです\n");
		//waitKey(0);
	}
	
	//csvファイルの書き込み
	fp = fopen( gaso_output, "w" );
	if( fp == NULL ){
	printf( "%sファイルが開けません\n", gaso_output );
	return -1;
	}

	for(int y=0;y<rows;y++){
		for(int x=0;x<cols;x++){
			fprintf( fp, "%d,",intensity[x][y]);
		}
			fprintf( fp, "\n");
	}
	fclose( fp );
	printf( "%sファイル書き込みが終わりました\n", gaso_output );
	
	return 0;
}

