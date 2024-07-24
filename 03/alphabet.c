#include <stdio.h>

#define ARRAY_SIZE 26 

int main() {
    int counts[ARRAY_SIZE] = {0}; //文字数をカウントする配列
    char c;

    printf("Enter a sentence: ");
    
    while ((c = getchar()) != '\n') { //文末まで
        // アルファベットかどうかを確認
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) { //アルファベットかどうか
            // 小文字に変換
            if (c >= 'A' && c <= 'Z') {
                c = c + ('a' - 'A'); // 大文字を小文字に変換(ASCIIコード上の差を利用する、二つの差を大文字に足すことで小文字に変換する)
            }
            counts[c - 'a']++; // 小文字のインデックスを利用してカウント('a' - 'a' は0になります。同様に、'b' - 'a' は1、'c' - 'a' は2と)
        }
    }

    for (int i = 0; i < ARRAY_SIZE; i++) { //アルファベットの配列を全て呼び出す
        if (counts[i] > 0) { //一回でもカウントされていたら
            printf("%c: %d\n", 'a' + i, counts[i]);
        }
    }

    return 0;
}
