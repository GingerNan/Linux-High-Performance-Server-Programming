// 代码清单6-1 CGI服务器
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

/**
 *  先关闭标准输出文件描述符 STDOUT_FILENO（值是1），然后复制socket文件描述符connf。
 * 因为dup总是返回系统中最小的可用文件描述符，所以它的返回值实际上是1，即之前关闭的标
 * 准输出文件描述符的值。
 *  这样一来，服务器输出到标准输出的内容（"abcd"）就会直接发送到与客户连接对应的socket
 * 上，因此printf调用的输出将被客户端获得（而不是显示在服务器程序的终端上）。
 */
int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret =bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(listenfd, (struct sockaddr*)&client, &client_addrlength);

    if (connfd < 0)
    {
        printf("errno is: %d\n", errno);
    }
    else
    {
        close(STDOUT_FILENO); // 关闭标准输出
        dup(connfd);          // 将connfd复制到标准输出
        printf("abcd\n");
        close(connfd);
    }

    close(listenfd);
    return 0;
}