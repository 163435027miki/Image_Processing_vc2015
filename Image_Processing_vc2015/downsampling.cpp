#include <string>
#include<sstream> //�����X�g���[��
#include<fstream>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include <direct.h>//�t�H���_���쐬����




char resize_filename[128];
char resize_derectroy[128];
char resize_output_NEAREST[128];
char resize_output_LINEAR[128];
char resize_output_CUBIC[128];
char resize_output_AREA[128];
char resize_output_LANCZOS4[128];
char resize_output_f[128];

int resizeN;

int Downsampling(char resize_filename[], char date[]) {

	//���̓t�@�C���̎w��
	sprintf(resize_derectroy, "..\\Input_deta\\%s.bmp", resize_filename);

	//�o�̓t�@�C���̐ݒ�
	sprintf(resize_output_f, "..\\output_deta\\%s", date);
	sprintf(resize_output_NEAREST, "%s\\%s_NEAREST.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_LINEAR, "%s\\%s_LINEAR.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_CUBIC, "%s\\%s_CUBIC.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_AREA, "%s\\%s_AREA.bmp", resize_output_f, resize_filename);
	sprintf(resize_output_LANCZOS4, "%s\\%s_LANCZOS4.bmp", resize_output_f, resize_filename);

	printf("input : %s\n", resize_derectroy);
	

	//�摜�̓ǂݍ���
	cv::Mat srcImg = cv::imread(resize_derectroy);

	printf("�ύX����T�C�Y�̔{�������\n");
	printf("�摜�� 1/n �{�ɂ���\n");
	printf("n= ");
	scanf("%d", &resizeN);

	//�o�͉摜�̈�̊m��
	cv::Mat dst_img1(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img2(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img3(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img4(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);
	cv::Mat dst_img5(srcImg.rows / resizeN, srcImg.cols / resizeN, CV_8UC3);

	//�摜�ό`
	cv::resize(srcImg, dst_img1, dst_img1.size(),1/resizeN, 1/resizeN, cv::INTER_NEAREST);			//�j�A���X�g�l�C�o�[�@
	cv::resize(srcImg, dst_img2, dst_img2.size(), 1 / resizeN, 1 / resizeN, cv::INTER_LINEAR);		//�o�C���j�A�@
	cv::resize(srcImg, dst_img3, dst_img3.size(), 1 / resizeN, 1 / resizeN, cv::INTER_CUBIC);		//�L���[�r�b�N�@
	cv::resize(srcImg, dst_img4, dst_img4.size(), 1 / resizeN, 1 / resizeN, cv::INTER_AREA);		//���A�����y��������
	cv::resize(srcImg, dst_img5, dst_img5.size(), 1 / resizeN, 1 / resizeN, cv::INTER_LANCZOS4);	//LANCZOS�t�B���^

	//�摜�\��
	cv::namedWindow("NEAREST", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("LINEAR", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("CUBIC", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("AREA", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("LANCZOS4", cv::WINDOW_AUTOSIZE);
	cv::imshow("NEAREST", dst_img1);
	cv::imshow("LINEAR", dst_img2);
	cv::imshow("CUBIC", dst_img3);
	cv::imshow("AREA", dst_img4);
	cv::imshow("LANCZOS4", dst_img5);

	//output��ۑ�����f�B���N�g���̍쐬
	if (_mkdir(resize_output_f) == 0) {
		printf("�t�H���_ %s ���쐬���܂���\n", resize_output_f);
	}
	else {
		printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n");
		//waitKey(0);
	}

	//�摜�ۑ�
	cv::imwrite(resize_output_NEAREST, dst_img1);
	cv::imwrite(resize_output_LINEAR, dst_img2);
	cv::imwrite(resize_output_CUBIC, dst_img3);
	cv::imwrite(resize_output_AREA, dst_img4);
	cv::imwrite(resize_output_LANCZOS4, dst_img5);

	cv::waitKey(0);

	return 0;
}
