// 代码清单7-1 测试进程的UID和EUID的区别

#include <unistd.h>
#include <stdio.h>

int main()
{
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("userid is %d\neffective userid is: %d\n",
        uid, euid);
    return 0;
}