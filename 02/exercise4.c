#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PASSWORD_LENGTH 12  // 生成するパスワードの長さ

int main() {
    FILE *random;
    unsigned char randomValue;
    int passwordIndex = 0;
    char password[PASSWORD_LENGTH + 1];  // 終端文字のために+1

    // /dev/random デバイスを開く
    random = fopen("/dev/random", "r");
    if (random == NULL) {
        perror("Failed to open /dev/random");
        return EXIT_FAILURE;
    }

    // パスワードの長さ分だけランダムな文字を生成
    while (passwordIndex < PASSWORD_LENGTH) {
        if (fread(&randomValue, 1, 1, random) == 1) {
            // 使用可能な文字にマッピング
            // '0'-'9', 'A'-'Z', 'a'-'z' の範囲に制限
            if ((randomValue >= '0' && randomValue <= '9') ||
                (randomValue >= 'A' && randomValue <= 'Z') ||
                (randomValue >= 'a' && randomValue <= 'z')) {
                password[passwordIndex++] = randomValue;
            }
        } else {
            fprintf(stderr, "Failed to read from /dev/random\n");
            fclose(random);
            return EXIT_FAILURE;
        }
    }

    // パスワードの終端を設定
    password[PASSWORD_LENGTH] = '\0';

    // パスワードを出力
    printf("Generated Password: %s\n", password);

    // ファイルを閉じる
    fclose(random);

    return EXIT_SUCCESS;
}
