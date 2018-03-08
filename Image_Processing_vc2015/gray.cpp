#include <string>
#include<sstream> //�����X�g���[��
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//�t�H���_���쐬����

char inputgray_directory[120] = "..\\Input_deta\\";							//inputimage�̏ꏊ
char outputgray_directory[120] = "..\\output_deta\\";						//outputiamge�̏ꏊ


char Output_gray_name[255];
char Input_gray_name[255];						//���̓t�@�C�����E���͌��̐ݒ�




char gray_filename[128];
char gray_derectroy[128];
char gray_output[128];
char gray_output_f[128];


using namespace std;
using namespace cv;

int gray_scale(char gray_filename[], char date[]) {

	for (int i = 1; i <= 45; ++i) {

		//���o�̓t�@�C���̎w��
//		sprintf(Input_gray_name, "%s%s.bmp", inputgray_directory, gray_filename);
//		sprintf(gray_output_f, "%s%s", outputgray_directory, date);
//		sprintf(Output_gray_name, "%s\\%s.bmp", gray_output_f, gray_filename);

//���o�̓t�@�C���̎w��
		sprintf(Input_gray_name, "%s%d.bmp", inputgray_directory, i);
		sprintf(gray_output_f, "%s%s", outputgray_directory, date);
		sprintf(Output_gray_name, "%s\\%d.bmp", gray_output_f, i);

		//�摜�̓ǂݍ���
		cv::Mat ImputImage = cv::imread(Input_gray_name);

		//�o�͉摜������ꏊ
		cv::Mat gray_image;

		//output��ۑ�����f�B���N�g���̍쐬
		if (_mkdir(gray_output_f) == 0) {
			printf("�t�H���_ %s ���쐬���܂���\n", gray_output_f);
		}
		else { printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n"); }

		//�O���[�X�P�[����
		cvtColor(ImputImage, gray_image, CV_RGB2GRAY);
/*
		//���O������
		std::string windowName = "image";
		cv::namedWindow(windowName);

		//��ʕ\��
		cv::imshow(windowName, gray_image);

		//�摜�̕ۑ�
		imwrite(Output_gray_name, gray_image);

		cv::waitKey(0);
		*/
		//�摜�̕ۑ�
		imwrite(Output_gray_name, gray_image);
	}
	return 0;
}