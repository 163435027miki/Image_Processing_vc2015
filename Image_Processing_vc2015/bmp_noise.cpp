#include <string>
#include<sstream> //�����X�g���[��
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//�t�H���_���쐬����



using namespace std;
using namespace cv;



char Output_Image_name[255];
char Input_Image_name[255];						//���̓t�@�C�����E���͌��̐ݒ�
char input_noise_name[255];
char inputimage_directory[120]="..\\Input_deta\\";							//inputimage�̏ꏊ
char outputimage_directory[120]="..\\output_deta\\";						//outputiamge�̏ꏊ
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

		////////////////////////////////�����ݒ�//////////////////////////////////////////////////////////////////

		int no_repeat_flag = 0;					//�J��Ԃ��Ȃ��Ƃ�1�ɂ���.���̂Ƃ��CIndependent_noise_name���w��D

	//////////////////���̓t�@�C���̃f�B���N�g������//////////////////////////////////////////////////////////

		//���̓t�@�C���̎w��
	//	sprintf(Input_Image_name, "%s%s.bmp", inputimage_directory, noise_filename);
	//	sprintf(noise_output_f, "%s%s", outputimage_directory, date);
	//	sprintf(input_csv_name, "%s\\%s.csv", noise_output_f, noise_filename);
		
		//���̓t�@�C���̎w��
		sprintf(Input_Image_name, "%s%d.bmp", inputimage_directory, kurikaeshi);
		sprintf(noise_output_f, "%s%s", outputimage_directory, date);
		sprintf(input_csv_name, "%s\\%s.csv", noise_output_f, noise_filename);
		
		//�摜�̓ǂݍ���
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
				//RGB�̕��ς���f�l�Ƃ���
				int B = ImputImage.at<Vec3b>(y, x)[0];
				int G = ImputImage.at<Vec3b>(y, x)[1];
				int R = ImputImage.at<Vec3b>(y, x)[2]; //printf("x=%d,y=%d\n", x, y);
				InputRGB[x][y] = (R + B + G) / 3;

			}
		}

		//�m�C�Y�̕t����������
		for (int repeat = 1; repeat <= repaet_max; ++repeat) {
			int sd_number = 10 * repeat;				//�W���΍���

			//�o�͉摜�̃f�B���N�g��
	//		sprintf(Output_Image_name, "%s\\%s_sd%d.bmp", noise_output_f, noise_filename, sd_number);		//�o�͉摜.bmp
	//		sprintf(output_csv_name, "%s\\%s_sd%d.csv", noise_output_f, noise_filename, sd_number);			//�o�͉摜�̉�f�l.csv

																											//�o�͉摜�̃f�B���N�g��
			sprintf(Output_Image_name, "%s\\%d_sd%d.bmp", noise_output_f, kurikaeshi, sd_number);		//�o�͉摜.bmp
			sprintf(output_csv_name, "%s\\%d_sd%d.csv", noise_output_f, kurikaeshi, sd_number);			//�o�͉摜�̉�f�l.csv

			std::vector<std::vector<int>>OutputRGB;
			OutputRGB.resize(cols);
			for (int i = 0; i < cols; ++i) {
				OutputRGB[i].resize(rows);
			}


			//�o�͉摜������ꏊ
			cv::Mat noise_image = cv::Mat::zeros(rows, cols, CV_8UC1);
			////////////////�m�C�Y�t��/////////////////////////////////////////////////////////////////////////////////////////////

			////////////////�m�C�Y��bmp��ǂݎ��p�^�[��//////////////////////////////////////////////////////////////////////////
			sprintf(input_noise_name, "%s%d�~%d\\sd%d.bmp", inputnoise_directory, cols, rows, sd_number);							//�m�C�Y�̉�f�l.bmp
			cv::Mat NoiseImage = cv::imread(input_noise_name);

			std::vector<std::vector<int>>NoiseRGB;
			NoiseRGB.resize(cols);
			for (int i = 0; i < cols; ++i) {
				NoiseRGB[i].resize(rows);
			}

			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					//RGB�̕��ς���f�l�Ƃ���
					int NB = NoiseImage.at<Vec3b>(y, x)[0];
					int NG = NoiseImage.at<Vec3b>(y, x)[1];
					int NR = NoiseImage.at<Vec3b>(y, x)[2];
					NoiseRGB[x][y] = (NR + NB + NG) / 3;

					//�m�C�Y�t���̌v�Z
					OutputRGB[x][y] = InputRGB[x][y] + NoiseRGB[x][y] - 128;
					if (OutputRGB[x][y] > 255)OutputRGB[x][y] = 255;
					if (OutputRGB[x][y] < 0)OutputRGB[x][y] = 0;
					//�摜�̔z��ɑ��
					noise_image.at<uchar>(y, x) = OutputRGB[x][y];

				}
			}

			///////////////�m�C�Y��CSV��ǂݎ��p�^�[��//////////////////////////////////////////////////////////////////////////
					/*
					sprintf(input_noise_name,"%s%d�~%d\\sd%d.bmp",inputnoise_directory,cols,rows,sd_number);							//�m�C�Y�̉�f�l.csv

					int i=0,j=0;

					int count_small=0;
					ifstream noise(input_noise_name);
					if(!noise){printf("%s������܂���\n",input_noise_name);return 1;}

					string str_noise;
						while(getline(noise,str_noise)){
						string token_noise;
						istringstream stream_noise(str_noise);

						while(getline(stream_noise,token_noise,',')){	//��s�ǂݎ��Dsd�̂݁C�J��Ԃ��͈͎̔w��ɗp����
							double tmp_noise=stof(token_noise);			//�����𐔎��ɕϊ�
							sd[count_small]=tmp_noise;				//�z��ɑ��

							OutputRGB[count_small][j]=InputRGB[count_small][j]+sd[count_small];
							if(OutputRGB[count_small][j]>255)OutputRGB[count_small][j]=255;
							if(OutputRGB[count_small][j]<0)OutputRGB[count_small][j]=0;

							noise_image.at<uchar>(j, i) = OutputRGB[count_small][j];

							++count_small;
							++i;
						}++j;count_small=0;i=0;
						}
				   */

				   //output��ۑ�����f�B���N�g���̍쐬
			if (_mkdir(noise_output_f) == 0) {
				printf("�t�H���_ %s ���쐬���܂���\n", noise_output_f);
			}
			else { printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n"); }

			//���͂����f�[�^��csv�Ƃ��ĕۑ�����
			fp_InputRGB = fopen(input_csv_name, "w");
			if (fp_InputRGB == NULL) {
				printf("%s�t�@�C�����J���܂���\n", input_csv_name);
				return -1;
			}

			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					fprintf(fp_InputRGB, "%d,", InputRGB[x][y]);
				}
				fprintf(fp_InputRGB, "\n");
			}
			fclose(fp_InputRGB);
			printf("%s�t�@�C���������݂��I���܂���\n", input_csv_name);

			//�摜�̕ۑ�
			FILE *fp_Output_image;
			fp_Output_image = fopen(output_csv_name, "w");
			if (fp_Output_image == NULL) {
				printf("%s�t�@�C�����J���܂���\n", output_csv_name);
				return -1;
			}
			for (int y = 0; y < rows; y++) {
				for (int x = 0; x < cols; x++) {
					fprintf(fp_Output_image, "%d,", OutputRGB[x][y]);
				}
				fprintf(fp_Output_image, "\n");
			}
			fclose(fp_Output_image);
			printf("%s�t�@�C���������݂��I���܂���\n", output_csv_name);

			imwrite(Output_Image_name, noise_image);

			//���O������
			std::string windowName[10] = { "1","2","3","4","5","6" };
			cv::namedWindow(windowName[repeat]);

			//��ʕ\��
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