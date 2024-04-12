#include <stdio.h>
#include <string.h> // strlen関数を使用するために必要

int addnum(void){
    int line_number = 1;
    char buffer[1024];

    while (1){
        if (!fgets(buffer, sizeof(buffer), stdin)){
            break;
        }
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
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