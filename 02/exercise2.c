#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192  // バッファのサイズを定義

int main(int argc, char *argv[]) {
    FILE *srcFile, *destFile;  // ファイルポインタ
    char buffer[BUFFER_SIZE];  // データ転送用のバッファ
    size_t bytesRead;

    // コマンドライン引数の数をチェック
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file destination_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    // コピー元ファイルをバイナリモードで開く
    srcFile = fopen(argv[1], "rb");
    if (srcFile == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    // コピー先ファイルをバイナリモードで開く
    destFile = fopen(argv[2], "wb");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(srcFile);
        return EXIT_FAILURE;
    }

    // ファイルをバッファサイズ単位で読み込み、書き込む
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    // ファイルを閉じる
    fclose(srcFile);
    fclose(destFile);

    return EXIT_SUCCESS;
}
