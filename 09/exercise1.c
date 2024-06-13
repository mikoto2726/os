#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

void count_file(const char *filename, int *lines, int *words, int *chars) {
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    char prev_char = '\0';
    
    *lines = *words = *chars = 0;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            (*chars)++;
            if (buffer[i] == '\n') {
                (*lines)++;
            }
            if ((buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') &&
                (prev_char != ' ' && prev_char != '\n' && prev_char != '\t')) {
                (*words)++;
            }
            prev_char = buffer[i];
        }
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int lines, words, chars;
    count_file(argv[1], &lines, &words, &chars);
    printf("%d %d %d %s\n", lines, words, chars, argv[1]);

    return 0;
}

