#include <stdio.h>

int main() {
    char line[1000]; // 1行の最大文字数を設定
    int lineNumber = 1; // 行番号を初期化

    // 標準入力から1行ずつ読み込む
    while (fgets(line, 1000, stdin)) {
        // 行番号とともに行を出力
        printf("%d %s", lineNumber, line);
        lineNumber++; // 行番号をインクリメント
    }

    return 0;
}
