#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    char buf[8192];
    int i, j, fd, rlen, wlen;

    for (i = 1; i < argc; i++) { /* skip argv[0] */
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) goto error;

        for (;;) {
            rlen = read(fd, buf, sizeof(buf));
            if (rlen < 0) goto error;
            if (rlen == 0) break; /* end of file */

            for (j = 0; j < rlen; ) {
                wlen = write(STDOUT_FILENO, buf + j, rlen - j);
                if (wlen < 0) goto error;

                j += wlen;
            }
        }
        close(fd);
    }

    return 0;

 error:
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
    if (fd >= 0) close(fd);
    return 1;
}

/*
char buf[8192]: 読み取ったデータを格納するバッファ。
int i, j: ループカウンター変数。
int fd: ファイルディスクリプターを格納する変数。
int rlen: 読み取ったデータの長さを格納する変数。
int wlen: 書き込んだデータの長さを格納する変数。

for (i = 1; i < argc; i++): コマンドライン引数で渡された各ファイル名に対してループを実行します（argv[0]はプログラム名なのでスキップ）。
fd = open(argv[i], O_RDONLY);: ファイルを読み取り専用でオープンし、ファイルディスクリプターをfdに格納します。エラーが発生した場合はgoto errorでエラーハンドリングへ飛びます。

for (;;): 無限ループでファイルからデータを読み取ります。
rlen = read(fd, buf, sizeof(buf));: ファイルからbufにデータを読み込み、読み取ったバイト数をrlenに格納します。エラーが発生した場合はgoto errorでエラーハンドリングへ飛びます。
if (rlen == 0) break;: ファイルの終わりに達した場合、ループを終了します。
for (j = 0; j < rlen; ): 読み取ったデータをバイトごとに書き込みます。
wlen = write(STDOUT_FILENO, buf + j, rlen - j);: 標準出力にデータを書き込み、書き込んだバイト数をwlenに格納します。エラーが発生した場合はgoto errorでエラーハンドリングへ飛びます。
j += wlen;: 書き込んだバイト数だけjを進めます。
close(fd);: ファイルを閉じます。

error:: エラーが発生した場合のラベル。
fprintf(stderr, "ERROR: %s\n", strerror(errno));: エラーメッセージを標準エラー出力に表示します。
if (fd >= 0) close(fd);: ファイルが開かれている場合、ファイルを閉じます。
return 1;: プログラムをエラー終了ステータス1で終了します。
*/