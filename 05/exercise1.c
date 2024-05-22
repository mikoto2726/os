#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 8192

int main(int argc, char* argv[])
{
    int src_fd = -1, dst_fd = -1;
    char buf[BUF_SIZE];
    ssize_t cnt, wlen;
    int i;

    if (argc != 3) {
        fprintf(stderr, "Usage: filecopy <src> <dest>\n");
        return 1;
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        fprintf(stderr, "Error opening source file: %s\n", strerror(errno));
        goto error;
    }
    
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (dst_fd < 0) {
        fprintf(stderr, "Error opening destination file: %s\n", strerror(errno));
        goto error;
    }

    for (;;) {
        cnt = read(src_fd, buf, sizeof(buf));
        if (cnt < 0) {
            fprintf(stderr, "Error reading from source file: %s\n", strerror(errno));
            goto error;
        }
        if (cnt == 0) break;  /* end of file */

        for (i = 0; i < cnt; ) {
            wlen = write(dst_fd, buf + i, cnt - i);
            if (wlen < 0) {
                fprintf(stderr, "Error writing to destination file: %s\n", strerror(errno));
                goto error;
            }
            i += wlen;
        }
    }

    close(dst_fd);
    close(src_fd);
    return 0;

 error:
    if (dst_fd >= 0) close(dst_fd);
    if (src_fd >= 0) close(src_fd);
    return 1;
}
