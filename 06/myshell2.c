#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void parse_input(char* input, char** argv, char** outfile) {
    char* token;
    int i = 0;
    *outfile = NULL;

    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARG_SIZE - 1) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                *outfile = token;
            }
            break;
        }
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[i] = NULL; // 最後の引数はNULLで終わる必要があります
}

int main() {
    char input[MAX_INPUT_SIZE];
    char* argv[MAX_ARG_SIZE];
    char* outfile;
    pid_t pid;
    int status;

    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        // 入力をトークンに分解
        parse_input(input, argv, &outfile);

        if (argv[0] == NULL) {
            continue; // 空行の場合は再度プロンプトを表示
        }

        // 'exit' コマンドを実装
        if (strcmp(argv[0], "exit") == 0) {
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            continue;
        } else if (pid == 0) {
            // 子プロセスでリダイレクトを設定
            if (outfile != NULL) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open failed");
                    exit(1);
                }
                if (dup2(fd, STDOUT_FILENO) < 0) {
                    perror("dup2 failed");
                    exit(1);
                }
                close(fd);
            }

            // 子プロセスでコマンドを実行
            if (execvp(argv[0], argv) < 0) {
                perror("execvp failed");
                exit(1);
            }
        } else {
            // 親プロセスで子プロセスの終了を待つ
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid failed");
            }
        }
    }

    return 0;
}
