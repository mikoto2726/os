#include <stdio.h>
#include <ctype.h> 

#define ARRAY_SIZE 26

int main() {
    int counts[ARRAY_SIZE] = {0}; 
    char c;

    printf("Enter a sentence: ");
    
    while ((c = getchar()) != '\n') {
        if (isalpha(c)) {
            c = tolower(c); 
            counts[c - 'a']++; 
        }
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (counts[i] > 0) { 
            printf("%c: %d\n", 'a' + i, counts[i]);
        }
    }
    return 0;
}
