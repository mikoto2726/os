#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000 // 1行あたりの最大文字数
#define DEFAULT_NUM_LINES 3  // デフォルトの表示行数

void mytail(FILE *file, int n) {
    char buffer[MAX_LINE_LENGTH];
    char* lines[n];
    int i = 0;

    // 最後のn行を読み込む
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        lines[i % n] = strdup(buffer); // strdup関数を使用してバッファのコピーを保存
        i++;
    }

    // 最後のn行を表示する
    for (int j = 0; j < n; j++) {
        printf("%s", lines[(i + j) % n]);
        free(lines[(i + j) % n]); // strdup関数で割り当てられたメモリを解放
    }
}

int main(int argc, char *argv[]) {
    int n = DEFAULT_NUM_LINES;
    FILE *fp;

    // コマンドライン引数から行数を取得する。デフォルトは3
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    // 標準入力からテキストデータを受け取り、最後のn行を表示する
    mytail(stdin, n);

    return 0;
}
