
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;


int main(int argc, char *argv[])
{
    int reterror = 0;

    if(argc != 3)
    {
        printf("illegal argument\r\n");
        exit(-1);
    }   
    else
        printf("argument %d - IP: %s Port: %s\r\n", argc, argv[1], argv[2]);

    /********** 创建socket **********/
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        fprintf(stderr ,"Failed to create socket: %d\n", sockfd);
        exit(-1);
    }

    /********** 连接目标server(IP&port) **********/
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    reterror = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(reterror < 0)
    {
        fprintf(stderr ,"Failed to connect socket: %d\n", reterror);
        exit(-1);
    }
   
    /********** 读取server回传的数据 **********/
    char buffer[256];
    read(sockfd, buffer, sizeof(buffer)-1);
    printf("message form server: %s\n", buffer);
   
    /********** 关闭socket **********/
    close(sockfd);
    
    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
