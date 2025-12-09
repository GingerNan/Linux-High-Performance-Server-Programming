## 主机字节序和网络字节序
字节序分为大端字节序(big endian)和小端字节序(little endian)
- 大端字节序：一个整数的高位字节存储在内存的低地址，低位字节存储在内存的高地址处
- 小端字节序：整数的高位字节存储在内存的高地址处，而低位字节存储在内存的高地址处

PC大多采用小端字节序，因此小端字节序又被称为主机字节序。大端又被称为网络字节序。
| JAVA虚拟机采用大端字节序

Linux提供了主机字节序和网络字节序之间的转换:
```c
#include <netinet/in.h>
// host to network long 即长整型的主机字节序数据转化为网络字节数据
unsigned long int htonl(unsigned long int hostlong);    
unsigned short int htons(unsigned long int hostshort);
unsigned long int ntonl(unsigned long int netlong);
unsigned short int ntons(unsigned long int netshort);
```
| 长整型函数通常用来转换IP地址，短整型函数用来转换端口号

## 通常socket地址
socket网络编程接口中表示socket地址的结构体sockaddr
```c
#include <bits/socket.h>
struct sockaddr
{
    sa_family_t sa_family;  // 地址族类型变量
    char sa_data[14];
}
```

协议族和地址族的关系
| 协议族 | 地址族 | 描述 |
| -- | -- | -- |
| PF_UNIX | AF_UNIX | UNIX本地域协议族 |
| PF_INET | AF_INET | TCP/IPv4协议族 |
| PF_INET6 | AF_INET6 | TCP/IPv6协议族 |

## 专用socket地址
TCP/IP协议族有sockaddr_in和sockaddr_in6两个专用socket地址结构体。
```c
struct sockaddr_in
{
    sa_family_t sa_family;      // 地址族：AF_INET
    u_int16_t sin_port;         // 端口号，要用网络字节序表示
    struct in_addr sin_addr;    // IPv4地址结构体
}
struct in_addr
{
    u_int32_t s_addr;           // IPv4地址，要用网络字节序表示
}
struct sockaddr_in6
{
    sa_family_t sin6_family;    // 地址族：AF_IENT6
    u_int16_t sin6_port;        // 端口号，要用网络字节序
    u_int32_t sin6_flowinfo;    // 流信息，应设置为0
    struct in6_addr sin6_addr;  // IPv6地址结构体
    u_int32_t sin6_scope_id;    // scope ID，尚处于实现阶段
}
struct in6_addr
{
    unsigned char sa_addr[16];  // IPv6地址，要用网络字节序表示
}
```

## IP地址转换函数
下面三个用于点分十进制字符串表示的IPv4和用网络字节序整数表示IPv4地址之间的转换
```c
#include <arpa/inet.h>
in_addr_t inet_addr(const char* strptr);
int inet_aton(const char* cp, struct in_addr* inp);
char* inet_ntoa(struct in_addr in);
```