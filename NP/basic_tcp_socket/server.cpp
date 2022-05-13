
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT  1796

using namespace std;


int main(int argc, char *argv[])
{
    int reterror = 0;

    /********** 创建socket **********/
    // int socket(int af, int type, int protocol);
    // af   // Address Family
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_fd < 0)
    {
        fprintf(stderr ,"Failed to create socket: %d\n", sock_fd);
        return -1;
    }

    // 设置套接字选项，允许端口重用
    // 否则受TIME_WAIT影响bind()失败
    int optvalue = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));
    
    /********** 将socket和IP&port绑定 **********/
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);
    // sockaddr_in其实解决了sockaddr结构体的缺陷，但需要强制转换
    reterror = bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(reterror < 0)
    {
        fprintf(stderr ,"Failed to bind socket: %d\n", reterror);
        return -1;
    }
    
    /********** 进入监听状态，等待用户发起请求 **********/
    // int listen( int sockfd, int backlog);
    // backlog   // 排队的最大连接个数
    reterror = listen(sock_fd, 5);
    if(reterror < 0)
    {
        fprintf(stderr ,"Failed to listen socket: %d\n", reterror);
        return -1;
    }
    
    /********** 接收客户端请求 **********/
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    // 阻塞调用
    int csock_fd = accept(sock_fd, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    
    /********** 向client发送数据 **********/
    char str[] = "Hello Summer";
    write(csock_fd, str, sizeof(str));
   
    /********** 关闭socket **********/
    close(csock_fd);
    close(sock_fd);
    
    return 0;
}

/*
// sockaddr_in结构体
struct sockaddr_in
{
    // 地址族
    sa_family_t sin_family;
    // 16位端口
    uint16_t sin_port;
    // 32位IP
    struct in_addr sin_addr;
    char sin_zero[8];
};

struct in_addr
{
    // 32位IP
    in_addr_t s_addr;
}
*/

//------------------------------//
//   River flows in summer
//------------------------------//
