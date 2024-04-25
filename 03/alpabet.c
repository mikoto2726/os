#include <stdio.h>
#include <ctype.h>

int main() {
    int counts[26] = {0}; // アルファベットの出現回数を保存する配列を初期化する

    // 標準入力から1文字ずつ読み込み、アルファベットの出現回数をカウントする
    int ch;
    while ((ch = getchar()) != EOF) {
        if (isalpha(ch)) { // アルファベットの場合
            ch = tolower(ch); // 大文字を小文字に変換する
            counts[ch - 'a']++; // アルファベットの出現回数をカウントする
        }
    }

    // アルファベットごとに出現回数を出力する
    for (int i = 0; i < 26; i++) {
        printf("%c:\n%d\n", 'a' + i, counts[i]);
    }

    return 0;
}
