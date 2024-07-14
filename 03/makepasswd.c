#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PASSWORD_LENGTH 12

int main(){
	FILE *random;
	unsigned char randomValue;
	int passwordIndex = 0;
	char password[PASSWORD_LENGTH + 1];

	random = fopen("/dev/random", "r");
	if (random == NULL){
		perror("Failed to open /dev/random");
		return EXIT_FAILURE;
	}

	while(passwordIndex < PASSWORD_LENGTH){
		if (fread(&randomValue, 1, 1, random) == 1){
			if ((randomValue >= '0' && randomValue <= '9') || (randomValue >= 'A' && randomValue <= 'Z') || (randomValue >= 'a' && randomValue <= 'z')){
				password[passwordIndex++] = randomValue;
			}
		}
		else {
			fprintf(stderr, "Failed to read from /dev/random\n");
			fclose(random);
			return EXIT_FAILURE;
		}
	}
	password[PASSWORD_LENGTH] = '\0';
	printf("Generated Password: %s\n", password);
	fclose(random);
	return EXIT_SUCCESS;
}
