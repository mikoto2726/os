#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buf[8192], errmsg[128];
    int len, fd = 0xdeadbeef;

    len = read(fd, buf, sizeof(buf));
    if (len < 0) {
        strerror_r(errno, errmsg, sizeof(errmsg));
        fprintf(stderr, "ERROR: %s\n", errmsg);
        return 1;
    }

    return 0;
}
/*
len = read(fd, buf, sizeof(buf));: fdからデータを読み取り、bufに格納します。sizeof(buf)は読み取る最大バイト数です。この場合、fdが無効なので、readは失敗しlenは負の値になります
if (len < 0): readが失敗した場合、errnoにエラーコードが設定されます。
strerror_r(errno, errmsg, sizeof(errmsg));: errnoに設定されたエラーコードに対応するエラーメッセージを取得し、errmsgに格納します。
fprintf(stderr, "ERROR: %s\n", errmsg);: エラーメッセージを標準エラー出力に表示します。
return 1;: エラーが発生した場合、プログラムを終了し、終了ステータスとして1を返します。
*/