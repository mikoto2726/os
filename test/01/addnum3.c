#include <stdio.h>
#include <string.h>

int main(void){
	int line = 1;
	char buffer[1024];

	while(1){
		if (!fgets(buffer, sizeof(buffer), stdin)){
			break;
		}
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len-1] == '\n'){
			buffer[len-1] = '\0';
		}
		printf("%d %s\n", line, buffer);
		line++;
	}
	return 0;
}
