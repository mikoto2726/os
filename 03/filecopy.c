#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
	FILE *srcFile, *destFile;
	char buffer[BUFFER_SIZE];
	size_t bytesRead;

	if (argc != 3){
		fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	srcFile = fopen(argv[1], "rb");
	if (srcFile == NULL){
		perror("Error opening source file");
		return EXIT_FAILURE;
	}

	destFile = fopen(argv[2], "rb");
	if (destFile == NULL){
		perror("Error opening destination file");
		fclose(srcFile);
		return EXIT_FAILURE;
	}

	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, srcFile)) > 0){
		fwrite(buffer, 1, bytesRead, destFile);
	}
	
	fclose(srcFile);
	fclose(destFile);

	return EXIT_SUCCESS;
}
