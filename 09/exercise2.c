#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	pid_t pid;
	int status;

	if (argc<2){
		fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0){
		execvp(argv[1], &argv[1]);
		perror("execvp");
		exit(EXIT_FAILURE);
	}else{
		if (waitpid(pid, &status, 0) == -1){
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status)){
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}else if (WIFSIGNALED(status)){
			printf("Child process killed by signal %d\n", WTERMSIG(status));
		}else{
			printf("Child process did not exit normally\n");
		}
	}
	return 0;
}
