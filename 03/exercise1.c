#include <stdio.h>

int main() {
    char c;
    
    printf("Enter a sentence: "); //入力を受け付ける
    while ((c = getchar()) != '\n') { //末尾に到達するまで
        if (c >= '0' && c <= '9') { //もし0－9の数字なら
            putchar('*'); //伏字にする
        } else {
            putchar(c); //ちがうならそのまま出力
        }
    }
    putchar('\n'); 
    return 0;
}
