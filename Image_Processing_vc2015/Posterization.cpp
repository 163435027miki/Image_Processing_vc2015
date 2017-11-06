#include <string>
#include<sstream> //�����X�g���[��
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//�t�H���_���쐬����

using namespace cv;

char post_filename[128];
char post_derectroy[128];
char post_output[128];
char post_output_f[128];

int gradationN;

int posterization(char post_filename[], char date[]) {

	printf("�|�X�^���[�[�V�������~����\n");
	printf("256������؂�Ȃ��ꍇ�͔����~���������܂�\n");
	printf("gradation_number = ");
	scanf("%d", &gradationN);

	//���o�̓t�@�C���̎w��
	sprintf(post_derectroy, "..\\Input_deta\\%s.bmp", post_filename);
	sprintf(post_output_f, "..\\output_deta\\%s", date);
	sprintf(post_output, "%s\\%s_post%d.bmp", post_output_f, post_filename, gradationN);

	//�摜�̓ǂݍ���
	cv::Mat ImputImage = cv::imread(post_derectroy);
	

	//�摜�T�C�Y�̎擾
	int cols = ImputImage.cols;	//x
	int rows = ImputImage.rows;	//y

	//�o�͉摜
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
	//��f�l�̎擾
	for (int y = 0; y<rows; y++) {
		for (int x = 0; x<cols; x++) {
			//int a=3*x;
			//intensity[x][y] = srcImg.at<unsigned char>(y, a); //X���W��x, Y���W��y�Ɉʒu����s�N�Z���̒l���擾
			//RGB�̕��ς���f�l�Ƃ���
			int B = ImputImage.at<Vec3b>(y, x)[0];
			int G = ImputImage.at<Vec3b>(y, x)[1];
			int R = ImputImage.at<Vec3b>(y, x)[2];
			intensity[x][y] = (R + B + G) / 3;
		}
	}
	
	double n1= ceil(float(256) / gradationN);
	int n =n1;//�؂�グ
	printf("gradationN=%d\n", gradationN);
	
	printf("n=%d\n",n);

	//�|�X�^���[�[�V��������
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

	//output��ۑ�����f�B���N�g���̍쐬
	if (_mkdir(post_output_f) == 0) {
		printf("�t�H���_ %s ���쐬���܂���\n", post_output_f);
	}
	else {
		printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n");
	}
	
	//�摜�̕ۑ�
	imwrite(post_output, make_image);

	//���O������
	std::string windowName = "post_image";
	cv::namedWindow(windowName);

	//��ʕ\��
	cv::imshow(windowName, make_image);

	cv::waitKey(0);
	
	return 0;

}