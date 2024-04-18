#include <stdio.h>

int main() {
    char line[1024];
    int lineNumber = 1;

    while (fgets(line, sizeof(line), stdin)) {
        printf("%d\t%s", lineNumber, line);
        lineNumber++;
    }

    return 0;
}
