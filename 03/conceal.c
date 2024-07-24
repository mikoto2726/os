#include <stdio.h>

int main() {
    char c;
    
    printf("Enter a sentence: ");
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            putchar('*');
        } else {
            putchar(c);
        }
    }
    putchar('\n'); 
    return 0;
}

