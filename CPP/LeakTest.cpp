
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>

using namespace std;


int count = 1;

void leak_test(int &count)
{
    int *stack_array = NULL;
    stack_array = (int *)malloc(sizeof(int)*128*1024*1024);
    if(stack_array != NULL)
        printf("Call leak_test() # %d\n", ++count);
}


int main(int argc, char **argv, char *env[])
{
    int count = 0;
    while( 1 )
    {
        leak_test(count);
        sleep(1);
    }

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
