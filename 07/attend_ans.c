#include <unistd.h>
#indlude <sys/wait.h>
#include <stdio.h>

int main(){
	pid_t pid = fork()
	if (pid > 0){
		int ret;
		waipid(pid,$ret,0);
		print("child return: %d\n", ret)
		return 0;
	}
	else{
		char cmd[] = {"ls", "-al", NULL};
	}
	
	//未完成
