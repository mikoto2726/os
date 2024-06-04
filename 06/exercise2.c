#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_command(char *line, char **args, char **input_file, char **output_file, int *append) {
    int i = 0;
    *input_file = NULL;
    *output_file = NULL;
    *append = 0;

    args[i] = strtok(line, " \t\n");
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            *output_file = strtok(NULL, " \t\n");
        } else if (strcmp(args[i], ">>") == 0) {
            *output_file = strtok(NULL, " \t\n");
            *append = 1;
        } else if (strcmp(args[i], "<") == 0) {
            *input_file = strtok(NULL, " \t\n");
        } else {
            i++;
            args[i] = strtok(NULL, " \t\n");
        }
    }
    args[i] = NULL;
}

void execute_command(char **args, char *input_file, char *output_file, int append) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (input_file != NULL) {
            int fd = open(input_file, O_RDONLY);
            if (fd == -1) {
                perror("open input file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (output_file != NULL) {
            int fd;
            if (append) {
                fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd == -1) {
                perror("open output file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (execvp(args[0], args) == -1) {
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("myshell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *input_file, *output_file;
    int append;
    
    while (1) {
        printf("myshell> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        parse_command(line, args, &input_file, &output_file, &append);

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        execute_command(args, input_file, output_file, append);
    }

    return 0;
}

