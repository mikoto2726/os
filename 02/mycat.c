#include <stdio.h>

int main(int argc, char* argv[]) {
    char buf[1024];
    int i;

    for (i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "r");
        while (fgets(buf, sizeof(buf), fp)) {
            fputs(buf, stdout);
        }
        fclose(fp);
    }
    return 0;
}