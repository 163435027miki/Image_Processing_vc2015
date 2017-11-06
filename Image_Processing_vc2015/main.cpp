#include <stdio.h>


char inputfile_directory[120]="..\\Input_deta\\";							//inputimageの場所
char outputfile_directory[120]="..\\output_deta\\";						//outputiamgeの場所
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

		printf("処理方法の選択\n");
		printf("画素値の取得 : 1\n");
		printf("ノイズ付加 : 2\n");
		printf("csvファイルからの画像作成 : 3\n");
		printf("画像を円形に切り抜く : 4\n");
		printf("ダウンサンプリング : 5\n");
		printf("ポスタリゼーション : 6\n");
		printf("処理方法 : ");

		scanf("%d", &selcect_processing);

		printf("入力データ(拡張子不要)の入力\n入力データ：");
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