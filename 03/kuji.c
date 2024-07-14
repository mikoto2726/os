#include <stdio.h>
#define LEN(a) (sizeof(a)/sizeof(a[0]))

int main(void){
	const char* t[] = {"健康", "金", "仕事", "恋愛"};
	const char* msg[] = {"大吉", "中吉", "小吉", "吉", "凶"};

	unsigned int r[LEN(t)], i; FILE* fp;

	fp = fopen("/dev/random", "rb");
	if (!fp){
		fprintf(stderr, "ERROR\n");
		return 1;
	}
	if (fread(r, sizeof(r[0]), LEN(r), fp) != LEN(r)){
		fprintf(stderr, "ERROR\n");
		return 1;
	}
	for (i = 0; i < LEN(t); i++){
		printf("今日の%s運: %s\n", t[i], msg[r[i] % LEN(msg)]);
	}
	fclose(fp);
	return 0;
}
