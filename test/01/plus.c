#include <stdio.h>

int main(int argc, char* argv[]){
	int a, b, n;
	n = scanf("%d %d", &a, &b);
	if (n != 2){
		fputs("ERROR\n", stderr);
		return 1;
	}
	printf("%d + %d = %d\n", a, b, a+b);
	return 0;
}
