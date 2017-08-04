#include <string>
#include<sstream> //文字ストリーム
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>

#include <tuple>
#include <direct.h>//フォルダを作成する

//int read_csv(int argc, char *argv[],const char *filename);
//int read_csv(const char *filename);
std::tuple<int, int, std::vector<std::vector<int>>> read_csv(const char *filename);
using namespace std;


int cols;
int rows;

char Make_Image_name[128];
//char Input_Image_name[128];						//入力ファイル名・入力元の設定
//char input_csv[255];
char inputcsv_directory[64]="..\\Input_deta\\";							//inputimageの場所
char outputbmp_directory[64]="..\\output_deta\\";						//outputiamgeの場所
char input_csv_directory[128];
char iutput_csv_name[128];
static int makeimage[1024];

char make_filename[128];
char make_derectroy[128];
char make_output[128];
char make_output_f[128];


//void itoa(int val, char *s);
//main
int make_csv_image(char read_csv_directory[],char date[]){

	//入出力ファイルの指定
	sprintf(input_csv_directory,"%s%s.csv",inputcsv_directory,read_csv_directory);
	sprintf(make_output_f,"%s%s", outputbmp_directory,date);
	sprintf(make_output,"%s\\%s.bmp",make_output_f,read_csv_directory);

	
	int argc;
	char** argv;
	//static int OutputRGB[256][256];

	std::vector<std::vector<int>>OutputRGB;
	OutputRGB.resize(256);
	for (int i = 0; i<256; ++i) {
		OutputRGB[i].resize(256);
	}
	

	//read_csv(argc,argv,input_csv_directory);
	//rows,cols=read_csv(input_csv_directory);
	std::tie(rows,cols, OutputRGB)=read_csv(input_csv_directory);

	 printf("行数 = %d\n", rows);
  printf("列数 = %d\n", cols);
	
////////////////////////////////初期設定//////////////////////////////////////////////////////////////////

/*
	cols=120;				//横幅
	rows=120;				//縦幅

	char use_name[128]="15-17p";
*/
	

////////////////////////InputImageの画素値の取得////////////////////////////////////////////////////////////////////////////////////
	
	




/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//cv::Mat make_image = cv::Mat::zeros(cols, rows, CV_8UC1);
	cv::Mat make_image = cv::Mat::zeros(rows, cols, CV_8UC1);

	/*
	int i=0,j=0;

	int count_small=0;
	ifstream make(iutput_csv_name);
	if(!make){printf("%sがありません\n",iutput_csv_name);return 1;}

	string str_make;
		while(getline(make,str_make)){
		string token_make;
        istringstream stream_make(str_make);
		
        while(getline(stream_make,token_make,',')){	//一行読み取る．makeimageのみ，繰り返しの範囲指定に用いる
			int tmp_make=stof(token_make);			//文字を数字に変換
			makeimage[count_small]=tmp_make;				//配列に代入
			
			OutputRGB[count_small][j]=makeimage[count_small];
			
			if(OutputRGB[count_small][j]>255)OutputRGB[count_small][j]=255;
			if(OutputRGB[count_small][j]<0)OutputRGB[count_small][j]=0;

			

			make_image.at<uchar>(j, i) = OutputRGB[count_small][j];

			++count_small;
			++i;
		}++j;count_small=0;i=0;
		}				
   
   */
	for (int j = 0; j < rows; ++j) {
		for (int i = 0; i < cols; ++i) {
			make_image.at<uchar>(j, i) = OutputRGB[i][j];
		}
	}
		FILE *fp_Output_image;

		//outputを保存するディレクトリの作成
		if (_mkdir(make_output_f) == 0) {
			printf("フォルダ %s を作成しました\n", make_output_f);
		}
		else { printf("フォルダ作成に失敗しました。もしくは作成済みです\n"); }


		fp_Output_image = fopen( make_output, "w" );
	if( fp_Output_image == NULL ){
		printf( "%sファイルが開けません\n", make_output );
		return -1;
	}
	for(int y=0;y<rows;y++){
		for(int x=0;x<cols;x++){

			fprintf( fp_Output_image, "%d,",OutputRGB[x][y]);
		}
			fprintf( fp_Output_image, "\n");
	}

	fclose( fp_Output_image );

	printf( "%sファイル書き込みが終わりました\n", make_output );

	imwrite(make_output,make_image); 

	 //名前をつける
	std::string windowName = "make_image";
	cv::namedWindow(windowName);

	//画面表示
	cv::imshow(windowName,make_image);
	 
 
	
		cv::waitKey(0);

	
   
	
}