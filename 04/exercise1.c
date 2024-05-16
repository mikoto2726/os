#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINES 3
#define MAX_LINE_LENGTH 1024

void mytail(int n, FILE *input) {
    char **lines = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        lines[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
        lines[i][0] = '\0';
    }

    int count = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, input)) {
        free(lines[count % n]);
        lines[count % n] = strdup(buffer);
        count++;
    }

    int start = count > n ? count % n : 0;
    int num_lines = count < n ? count : n;
    for (int i = 0; i < num_lines; i++) {
        printf("%s", lines[(start + i) % n]);
        free(lines[(start + i) % n]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    int n = DEFAULT_LINES;
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n <= 0) {
            fprintf(stderr, "Invalid number of lines: %d\n", n);
            return 1;
        }
    }

    mytail(n, stdin);
    return 0;
}
