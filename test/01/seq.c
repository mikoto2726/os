#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	char buf[80];
	int i, n;

	if (argc != 2){
		fputs("ERROR\n", stderr);
		return 1;
	}
	n = atoi(argv[1]);
	while(gets(buf)){
		for (i = 0; i < n; i++){
			puts(buf);
		}
	}
	return 0;
}
	
	
