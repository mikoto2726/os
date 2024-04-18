#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("時刻を指定してください\n");
        return 1;
    }

    int hour = atoi(argv[1]);
    
    if (hour >= 5 && hour <= 10) {
        printf("おはようございます\n");
    }
    else if (hour >= 11 && hour <= 17) {
        printf("こんにちは\n");
    }
    else if (hour >= 18 && hour <= 20) {
        printf("こんばんわ\n");
    }
    else if ((hour >= 0 && hour <= 4) || (hour >= 21 && hour <= 23)) {
        printf("おやすみなさい\n");
    }
    else {
        printf("無効な時刻が指定されました\n");
    }

    return 0;

}
