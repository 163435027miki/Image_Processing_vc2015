#include <opencv2/opencv.hpp>
#include<math.h>
#include <string>
#include<sstream> //�����X�g���[��
#include <direct.h>//�t�H���_���쐬����



using namespace cv;
		int intensity[513][513];//�o�͌��ʂ��i�[
		FILE *fp;
		

	char input[128];

	char fname[128];

	char gaso_filename[128];
	char gaso_derectroy[128];
	char gaso_output[128];
	char gaso_output_f[128];

int gaso(char gaso_filename[],char date[])
{
	
	//���o�̓t�@�C���̎w��
	sprintf(gaso_derectroy,"..\\Input_deta\\%s.bmp",gaso_filename);
	sprintf(gaso_output_f,"..\\output_deta\\%s",date);
	sprintf(gaso_output,"%s\\%s.csv",gaso_output_f,gaso_filename);

	printf("input : %s\n",gaso_derectroy);
	printf("output : %s\n",gaso_output);
	
	//�摜�̓ǂݍ���
	cv::Mat srcImg = cv::imread(gaso_derectroy);

	//�摜�T�C�Y�̎擾
	int cols=srcImg.cols;
	int rows=srcImg.rows;

	//��f�l�̎擾
	for(int y=0;y<rows;y++){
		for(int x=0;x<cols;x++){
			//int a=3*x;
				//intensity[x][y] = srcImg.at<unsigned char>(y, a); //X���W��x, Y���W��y�Ɉʒu����s�N�Z���̒l���擾

			//RGB�̕��ς���f�l�Ƃ���
				int B = srcImg.at<Vec3b>(y, x)[0];
				int G = srcImg.at<Vec3b>(y, x)[1];
				int R = srcImg.at<Vec3b>(y, x)[2];
				intensity[x][y]=(R+B+G)/3;
		}
	}

    //waitKey(0);

	//output��ۑ�����f�B���N�g���̍쐬
	if (_mkdir(gaso_output_f) == 0) {
		printf("�t�H���_ %s ���쐬���܂���\n", gaso_output_f);
	}
	else {
		printf("�t�H���_�쐬�Ɏ��s���܂����B�������͍쐬�ς݂ł�\n");
		//waitKey(0);
	}
	
	//csv�t�@�C���̏�������
	fp = fopen( gaso_output, "w" );
	if( fp == NULL ){
	printf( "%s�t�@�C�����J���܂���\n", gaso_output );
	return -1;
	}

	for(int y=0;y<rows;y++){
		for(int x=0;x<cols;x++){
			fprintf( fp, "%d,",intensity[x][y]);
		}
			fprintf( fp, "\n");
	}
	fclose( fp );
	printf( "%s�t�@�C���������݂��I���܂���\n", gaso_output );
	
	return 0;
}

