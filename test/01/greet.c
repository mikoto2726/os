#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc == 2){
		int hour = atoi(argv[1]);
		if (5 <= hour && hour <= 10){
			printf("おはようございます\n");
		}
		else if (11 <= hour && hour <= 17){
			printf("こんにちは\n");
		}
		else if (18 <= hour && hour <= 20){
			printf("こんばんは\n");
		}
		else if (0 <= hour && hour <= 4){
			printf("おやすみなさい\n");
		}
		else if (21 <= hour && hour <=23){
			printf("おやすみなさい\n");
		}
		else{
			printf("0~23で入力して下さい\n");
	
		}
	}	
	else{
		printf("時間を指定してください\n");
	}
}
