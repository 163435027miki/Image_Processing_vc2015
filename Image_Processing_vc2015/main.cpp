#include <stdio.h>


char inputfile_directory[120]="..\\Input_deta\\";							//inputimage�̏ꏊ
char outputfile_directory[120]="..\\output_deta\\";						//outputiamge�̏ꏊ
char deta[128];
//char inputnoise_directory[120]="..\\Input_deta\\Input_noise_csv\\";

int timeset(char date[]);
int gaso(char input_deta[],char date[]);
int bmp_noise(char input_deta[],char date[]);
int make_csv_image(char input_deta[],char date[]);
int circle_cut(char input_deta[], char date[]);
int Downsampling(char input_deta[], char date[]);
int posterization(char noise_filename[], char date[]);

int main(){
	
	int selcect_processing;
	char input_deta[128];
	char *inputdeta_directory;
	int a;
	char b[64]="";

	while (1) {

		timeset(deta);

		printf("�������@�̑I��\n");
		printf("��f�l�̎擾 : 1\n");
		printf("�m�C�Y�t�� : 2\n");
		printf("csv�t�@�C������̉摜�쐬 : 3\n");
		printf("�摜���~�`�ɐ؂蔲�� : 4\n");
		printf("�_�E���T���v�����O : 5\n");
		printf("�|�X�^���[�[�V���� : 6\n");
		printf("�������@ : ");

		scanf("%d", &selcect_processing);

		printf("���̓f�[�^(�g���q�s�v)�̓���\n���̓f�[�^�F");
		scanf("%s", &input_deta);
		//sprintf(inputdeta_directory,"%s%s",inputfile_directory,input_deta);


		if (selcect_processing == 1)gaso(input_deta, deta);
		if (selcect_processing == 2)bmp_noise(input_deta, deta);
		if (selcect_processing == 3)make_csv_image(input_deta, deta);
		if (selcect_processing == 4)circle_cut(input_deta, deta);
		if (selcect_processing == 5)Downsampling(input_deta, deta);
		if (selcect_processing == 6)posterization(input_deta, deta);
	}
	
}