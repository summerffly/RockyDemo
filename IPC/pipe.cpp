
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX API (Unix,Linux,masOS)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;


int main(int argc, char **argv, char *env[])
{
    const char data[] = "hello summer";
    char buffer[128];
    // 清空缓冲区
    memset(buffer, 0, sizeof(buffer));

    // popen()是基于文件流(FILE)的
    // 而pipe()是基于文件描述符(fd)的
    // 管道fd[0]用于读取，fd[1]用于写入
    int filedes[2];
    if(pipe(filedes) != 0)
       exit(-1);

    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr, "fork failure");
        exit(-2);
    }
    if(pid == 0)   // 子进程
    {
        int ret = read(filedes[0], buffer, 128);
        printf("Read %d bytes: %s\n", ret, buffer);
        
        return 0;
    }
    else   // 父进程
    {
        int ret = write(filedes[1], data, strlen(data));
        printf("Wrote %d bytes: %s\n", ret, data);
        
        return 0;
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
