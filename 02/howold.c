#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        printf("Failed to open /proc/uptime\n");
        return 1;
    }

    double uptime;
    fscanf(fp, "%lf", &uptime);
    fclose(fp);

    int hours = (int)uptime / 3600;
    int minutes = ((int)uptime % 3600) / 60;
    int seconds = (int)uptime % 60;

    printf("Up for %02d:%02d:%02d\n", hours, minutes, seconds);

    return 0;
}
