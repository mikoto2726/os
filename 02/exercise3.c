#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    double uptime, idleTime;

    // /proc/uptime ファイルを開く
    file = fopen("/proc/uptime", "r");
    if (file == NULL) {
        perror("Failed to open /proc/uptime");
        return EXIT_FAILURE;
    }

    // uptime を読み取る
    if (fscanf(file, "%lf %lf", &uptime, &idleTime) != 2) {
        fprintf(stderr, "Failed to read uptime from /proc/uptime\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    // ファイルを閉じる
    fclose(file);

    // 稼働時間を表示
    printf("Up for : %.2f seconds\n", uptime);

    return EXIT_SUCCESS;
}
