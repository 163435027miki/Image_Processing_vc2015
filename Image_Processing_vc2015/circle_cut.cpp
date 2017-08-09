#include <string>
#include<sstream> //�����X�g���[��
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//�t�H���_���쐬����

char cut_filename[128];
char cut_derectroy[128];
char cut_output[128];
char cut_output_f[128];

int circle_cut(char cut_filename[], char date[]) {

	//���a����]����ݒ肷��
	int margin = 5;

	//���o�̓t�@�C���̎w��
	sprintf(cut_derectroy, "..\\Input_deta\\%s.bmp", cut_filename);
	sprintf(cut_output_f, "..\\output_deta\\%s", date);
	sprintf(cut_output, "%s\\%s_cut.bmp", cut_output_f, cut_filename);

	//�摜�̓ǂݍ���
	cv::Mat ImputImage = cv::imread(cut_derectroy);

	//�摜�T�C�Y�̎擾
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


	//�~���}�X�N�Ƃ��ĕ`��
	cv::Mat circle = cv::Mat::zeros(cols, rows, CV_8UC3);
	cv::circle(circle, cv::Point(cols_center, rows_center), radius, cv::Scalar(255, 255, 255), -1, 8);
	
	//���F�w�i�̉摜
	cv::Mat OutputImage = cv::Mat::zeros(cols, rows, CV_8UC3);

	//IplImage* src = cvLoadImage(cut_derectroy, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	//�}�X�N�̈ʒu�̂݃R�s�[����
	ImputImage.copyTo(OutputImage, circle);

	//output��ۑ�����f�B���N�g���̍쐬
	if (_mkdir(cut_output_f) == 0) {
		printf("�t�H���_ %s ���쐬���܂���\n", cut_output_f);
	}
	else {
		printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n");
	}

	
	//�摜�̕ۑ�
	imwrite(cut_output, OutputImage);

	//���O������
	std::string windowName = "cut_image";
	cv::namedWindow(windowName);

	//��ʕ\��
	cv::imshow(windowName, OutputImage);

	cv::waitKey(0);

	return 0;

}