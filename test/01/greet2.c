#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int n, hour;
	n = argc;
	if (n == 2){
		hour = atoi(argv[1]);
		if (5 <= hour && hour <= 10){
		printf("おはようございます\n");
		}
	}
}
