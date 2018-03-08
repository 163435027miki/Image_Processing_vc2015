#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//フォルダを作成する



using namespace std;
using namespace cv;



char Output_Image_name[255];
char Input_Image_name[255];						//入力ファイル名・入力元の設定
char input_noise_name[255];
char inputimage_directory[120]="..\\Input_deta\\";							//inputimageの場所
char outputimage_directory[120]="..\\output_deta\\";						//outputiamgeの場所
char inputnoise_directory[120]="..\\Input_deta\\Input_noise_csv\\";
char input_csv_name[255];
char output_csv_name[255];
char sd[255];
int repaet_max=5;
int repeat_count=0;

char noise_filename[128];
char noise_derectroy[128];
char noise_output[128];
char noise_output_f[128];



//main
int bmp_noise(char noise_filename[],char date[]) {

	for (int kurikaeshi = 1; kurikaeshi <= 180; ++kurikaeshi) {
		FILE *fp_InputRGB;

		////////////////////////////////初期設定//////////////////////////////////////////////////////////////////

		int no_repeat_flag = 0;					//繰り返さないとき1にする.このとき，Independent_noise_nameを指定．

	//////////////////入力ファイルのディレクトリ生成//////////////////////////////////////////////////////////

		//入力ファイルの指定
	//	sprintf(Input_Image_name, "%s%s.bmp", inputimage_directory, noise_filename);
	//	sprintf(noise_output_f, "%s%s", outputimage_directory, date);
	//	sprintf(input_csv_name, "%s\\%s.csv", noise_output_f, noise_filename);
		
		//入力ファイルの指定
		sprintf(Input_Image_name, "%s%d.bmp", inputimage_directory, kurikaeshi);
		sprintf(noise_output_f, "%s%s", outputimage_directory, date);
		sprintf(input_csv_name, "%s\\%s.csv", noise_output_f, noise_filename);
		
		//画像の読み込み
		cv::Mat ImputImage = cv::imread(Input_Image_name);

		int rows = ImputImage.rows;
		int cols = ImputImage.cols;
		printf("rows=%d,cols=%d\n", rows, cols);
		std::vector<std::vector<int>>InputRGB;
		/*
		InputRGB.resize(rows);
		for(int i=0;i<rows;++i){
				InputRGB[i].resize(cols);
		}
		*/
		InputRGB.resize(cols);
		for (int i = 0; i < cols; ++i) {
			InputRGB[i].resize(rows);
		}
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				//RGBの平均を画素値とする
				int B = ImputImage.at<Vec3b>(y, x)[0];
				int G = ImputImage.at<Vec3b>(y, x)[1];
				int R = ImputImage.at<Vec3b>(y, x)[2]; //printf("x=%d,y=%d\n", x, y);
				InputRGB[x][y] = (R + B + G) / 3;

			}
		}

		//ノイズの付加ここから
		for (int repeat = 1; repeat <= repaet_max; ++repeat) {
			int sd_number = 10 * repeat;				//標準偏差σ

			//出力画像のディレクトリ
	//		sprintf(Output_Image_name, "%s\\%s_sd%d.bmp", noise_output_f, noise_filename, sd_number);		//出力画像.bmp
	//		sprintf(output_csv_name, "%s\\%s_sd%d.csv", noise_output_f, noise_filename, sd_number);			//出力画像の画素値.csv

																											//出力画像のディレクトリ
			sprintf(Output_Image_name, "%s\\%d_sd%d.bmp", noise_output_f, kurikaeshi, sd_number);		//出力画像.bmp
			sprintf(output_csv_name, "%s\\%d_sd%d.csv", noise_output_f, kurikaeshi, sd_number);			//出力画像の画素値.csv

			std::vector<std::vector<int>>OutputRGB;
			OutputRGB.resize(cols);
			for (int i = 0; i < cols; ++i) {
				OutputRGB[i].resize(rows);
			}


			//出力画像を入れる場所
			cv::Mat noise_image = cv::Mat::zeros(rows, cols, CV_8UC1);
			////////////////ノイズ付加/////////////////////////////////////////////////////////////////////////////////////////////

			////////////////ノイズのbmpを読み取るパターン//////////////////////////////////////////////////////////////////////////
			sprintf(input_noise_name, "%s%d×%d\\sd%d.bmp", inputnoise_directory, cols, rows, sd_number);							//ノイズの画素値.bmp
			cv::Mat NoiseImage = cv::imread(input_noise_name);

			std::vector<std::vector<int>>NoiseRGB;
			NoiseRGB.resize(cols);
			for (int i = 0; i < cols; ++i) {
				NoiseRGB[i].resize(rows);
			}

			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					//RGBの平均を画素値とする
					int NB = NoiseImage.at<Vec3b>(y, x)[0];
					int NG = NoiseImage.at<Vec3b>(y, x)[1];
					int NR = NoiseImage.at<Vec3b>(y, x)[2];
					NoiseRGB[x][y] = (NR + NB + NG) / 3;

					//ノイズ付加の計算
					OutputRGB[x][y] = InputRGB[x][y] + NoiseRGB[x][y] - 128;
					if (OutputRGB[x][y] > 255)OutputRGB[x][y] = 255;
					if (OutputRGB[x][y] < 0)OutputRGB[x][y] = 0;
					//画像の配列に代入
					noise_image.at<uchar>(y, x) = OutputRGB[x][y];

				}
			}

			///////////////ノイズのCSVを読み取るパターン//////////////////////////////////////////////////////////////////////////
					/*
					sprintf(input_noise_name,"%s%d×%d\\sd%d.bmp",inputnoise_directory,cols,rows,sd_number);							//ノイズの画素値.csv

					int i=0,j=0;

					int count_small=0;
					ifstream noise(input_noise_name);
					if(!noise){printf("%sがありません\n",input_noise_name);return 1;}

					string str_noise;
						while(getline(noise,str_noise)){
						string token_noise;
						istringstream stream_noise(str_noise);

						while(getline(stream_noise,token_noise,',')){	//一行読み取る．sdのみ，繰り返しの範囲指定に用いる
							double tmp_noise=stof(token_noise);			//文字を数字に変換
							sd[count_small]=tmp_noise;				//配列に代入

							OutputRGB[count_small][j]=InputRGB[count_small][j]+sd[count_small];
							if(OutputRGB[count_small][j]>255)OutputRGB[count_small][j]=255;
							if(OutputRGB[count_small][j]<0)OutputRGB[count_small][j]=0;

							noise_image.at<uchar>(j, i) = OutputRGB[count_small][j];

							++count_small;
							++i;
						}++j;count_small=0;i=0;
						}
				   */

				   //outputを保存するディレクトリの作成
			if (_mkdir(noise_output_f) == 0) {
				printf("フォルダ %s を作成しました\n", noise_output_f);
			}
			else { printf("フォルダ作成に失敗しました。もしくは作成済みです\n"); }

			//入力したデータをcsvとして保存する
			fp_InputRGB = fopen(input_csv_name, "w");
			if (fp_InputRGB == NULL) {
				printf("%sファイルが開けません\n", input_csv_name);
				return -1;
			}

			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					fprintf(fp_InputRGB, "%d,", InputRGB[x][y]);
				}
				fprintf(fp_InputRGB, "\n");
			}
			fclose(fp_InputRGB);
			printf("%sファイル書き込みが終わりました\n", input_csv_name);

			//画像の保存
			FILE *fp_Output_image;
			fp_Output_image = fopen(output_csv_name, "w");
			if (fp_Output_image == NULL) {
				printf("%sファイルが開けません\n", output_csv_name);
				return -1;
			}
			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					fprintf(fp_Output_image, "%d,", OutputRGB[x][y]);
				}
				fprintf(fp_Output_image, "\n");
			}
			fclose(fp_Output_image);
			printf("%sファイル書き込みが終わりました\n", output_csv_name);

			imwrite(Output_Image_name, noise_image);

			//名前をつける
			std::string windowName[10] = { "1","2","3","4","5","6" };
			cv::namedWindow(windowName[repeat]);

			//画面表示
			cv::imshow(windowName[repeat], noise_image);


			// cv::destroyWindow(windowName);
			if (no_repeat_flag == 1) {
				cv::waitKey(20);
				cv::destroyWindow(windowName[repeat]);
				break;
			}
			++repeat_count;
			if (repeat_count == repaet_max) {
				cv::waitKey(20);
				//cv::destroyWindow(windowName);
			}
		}
	}
}