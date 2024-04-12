#include <stdio.h>
#include <stdlib.h>

int addnum(void){
    int line_number = 1;
    char buffer[1024];

    while (gets(buffer, sizeof(buffer), stdin)){
        if (feof(buffer)){
            break;
        }
        char text = line_number + buffer;
        puts(text);
        line_number++;
    }
    return 0;
}