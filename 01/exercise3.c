#include <stdio.h>

int main(int n){
    char message;
    if (5<n<10){
        message = "おはようございます";
        return message;
    }

    if (11<n<17){
        message = "こんにちは";
        return message;
    }

    if (18<n<20){
        message = "こんばんは";
        return message;
    }

    if (0<n<4 | 21<n<23){
        message = "おやすみなさい";
        return message;
    }

    else{
        message = "時間を指定してください";
        return message;
    }
}