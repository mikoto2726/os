#include <stdio.h>

int main(void){
	
	int line = 1;
	char buffer[1024];

	while(1){

		if (! gets(buffer)){
		       break;
		}
		printf("%d, %s\n",line, buffer);
		line++;
	}
	return 0;
}
