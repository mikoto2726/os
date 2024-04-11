#include <stdio.h>
#include <stdlib.h>

void greet(int hour){

    if (hour >= 5 && hour <= 10){
        printf("おはようございます\n");
    }

    else if (hour >= 11 && hour <=17){
        printf("こんにちは\n");
    }

    else if (hour >= 18 && hour <=20){
        printf("こんばんは\n");
    }

    else if ((hour >= 0 && hour <= 4) || (hour >= 21 && hour <= 23)){
        printf("おやすみなさい\n");
    }

    else{
        printf("時間を指定してください\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) { // コマンドライン引数が1つ提供された場合
        int hour = atoi(argv[1]);
        greet(hour);
    } else {
        printf("時間を指定してください\n");
    }
    return 0;
}