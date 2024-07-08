#include <stdio.h>

int addnum(void){
    int line_number = 1;
    char buffer[1024];

    while (1){
        if (!gets(buffer)){
            break;
        }
        printf("%d %s\n", line_number, buffer);
        line_number++;
    }
    return 0;
}

int main(void){
    addnum();
    return 0;
}
