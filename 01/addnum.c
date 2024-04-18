#include <stdio.h>

int main() {
    char line[1024];
    int lineNumber = 1;

    while (gets(line)) {
        printf("%d\t%s\n", lineNumber, line);
        lineNumber++;
    }

    return 0;
}
