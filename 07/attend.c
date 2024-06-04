#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        execlp("ls", "ls", "-al", (char *)NULL);
        perror("execlp failed");
        exit(1);
    } else {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("子プロセスは正常に終了しました。終了ステータス: %d\n", WEXITSTATUS(status));
        } else {
            printf("子プロセスは異常終了しました。\n");
        }
    }

    return 0;
}

