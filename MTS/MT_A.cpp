
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>     // POSIX API (Unix,Linux,masOS)
#include <pthread.h>    // POSIX Thread
#include <stdlib.h>     // C Standard Library
#include <stdio.h>

#define THSCALE   100

using namespace std;


// Thread Function Declaration
void *Thread_Func(void *args);

int g_count;
int g_tid[THSCALE];
int g_thcount[THSCALE];

int main(int argc, char **argv, char *env[])
{    
    pthread_t tid[THSCALE];
    //void *status;

    for (int i = 0; i < 10; i++)
	{
        g_count = 0;
		for (int j = 0; j < THSCALE; j++)
		{
			g_tid[j] = j;
			g_thcount[j] = 0;
		}

		for (int j = 0; j < THSCALE; j++)
		{
			pthread_create(&tid[j], NULL, Thread_Func, (void *)&g_tid[j]);
		}
        sleep(2);
		printf("#%d  g_count = %d \n", i, g_count);
		fflush(stdout);
	}

    printf("Process #%d FINISHED\n", getpid());
    exit(EXIT_SUCCESS);
}

void *Thread_Func(void *args)
{
	int *tid = (int *)args;
    for (int i = 0; i < 10000; i++)
	{
		g_thcount[*tid]++;
		g_count++;
	}
	//printf("ThreadID: %d Count=%d\n", *tid, g_thcount[*tid]);
    
    pthread_exit(NULL);
}


//------------------------------//
//   River flows in summer
//------------------------------//
