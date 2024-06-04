#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_command(char *line, char **args) {
    int i = 0;
    args[i] = strtok(line, " \t\n");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " \t\n");
    }
}

void execute_command(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // 子プロセス: コマンドを実行する
        if (execvp(args[0], args) == -1) {
            perror("myshell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // fork失敗
        perror("myshell");
    } else {
        // 親プロセス: 子プロセスの終了を待つ
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    
    while (1) {
        printf("myshell> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        parse_command(line, args);

        if (args[0] == NULL) {
            continue;
        }

        // "exit" コマンドを実装
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        execute_command(args);
    }

    return 0;
}

