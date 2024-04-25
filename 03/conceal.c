#include <stdio.h>
#include <ctype.h>

int main() {
    int ch;

    // 標準入力から1文字ずつ読み込み、数字を伏せ字に変換して出力する
    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) { // 文字が数字の場合
            putchar('*'); // 伏せ字'*'に変換して出力
        } else {
            putchar(ch); // 数字以外の場合はそのまま出力
        }
    }

    return 0;
}
