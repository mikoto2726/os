#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *srcFile, *destFile;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    // 引数のチェック
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
        return 1;
    }

    // ソースファイルを開く
    srcFile = fopen(argv[1], "rb");
    if (srcFile == NULL) {
        perror("Failed to open source file");
        return 1;
    }

    // デスティネーションファイルを開く
    destFile = fopen(argv[2], "wb");
    if (destFile == NULL) {
        perror("Failed to open destination file");
        fclose(srcFile);
        return 1;
    }

    // ファイルをコピーする
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    // ファイルを閉じる
    fclose(srcFile);
    fclose(destFile);

    return 0;
}
