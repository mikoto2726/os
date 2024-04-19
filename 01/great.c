#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("時刻を指定してください\n");
        return 1;
    }

    int time = atoi(argv[1]);
    if(time >= 5 && time <= 10) {
        printf("おはようございます\n");
    } else if(time >= 11 && time <= 17) {
        printf("こんにちは\n");
    } else if(time >= 18 && time <= 20) {
        printf("こんばんは\n");
    } else if((time >= 0 && time <= 4) || (time >= 21 && time <= 23)) {
        printf("おやすみなさい\n");
    } else {
        printf("無効な時刻です\n");
    }

    return 0;
}
