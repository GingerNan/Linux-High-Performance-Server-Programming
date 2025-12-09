#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    // 1. 将字符串IP转为struct in_addr类型
    struct in_addr addr1, addr2;
    addr1.s_addr = inet_addr("1.2.3.4");
    addr2.s_addr = inet_addr("10.194.71.60");

    // 2. 用独立缓冲区存储结果，避免覆盖
    char szValue1[INET_ADDRSTRLEN] = {0};
    char szValue2[INET_ADDRSTRLEN] = {0};
    strcpy(szValue1, inet_ntoa(addr1));
    strcpy(szValue2, inet_ntoa(addr2));

    // 3. 正确打印
    printf("address 1: %s\n", szValue1);
    printf("address 2: %s\n", szValue2);
    return 0;
}