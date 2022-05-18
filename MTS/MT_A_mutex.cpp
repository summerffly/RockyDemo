
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

pthread_mutex_t g_mutex;
int g_count;
int g_tid[THSCALE];
int g_thcount[THSCALE];


int main(int argc, char **argv, char *env[])
{    
    pthread_t tid[THSCALE];
    //void *status;

	int res = pthread_mutex_init(&g_mutex, NULL);
	if(res != 0)
	{
		perror("pthread_mutex_init() failed \n");
		exit(EXIT_FAILURE);
	}
	else
		printf("pthread_mutex_init() suceed \n");

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
	}

	res = pthread_mutex_destroy(&g_mutex);
	if(res == 0)
		printf("pthread_mutex_destroy suceed() \n");

    printf("Process #%d FINISHED \n", getpid());
    exit(EXIT_SUCCESS);
}

void *Thread_Func(void *args)
{
	int *tid = (int *)args;
    for (int i = 0; i < 10000; i++)
	{
		g_thcount[*tid]++;
		pthread_mutex_lock(&g_mutex);
		g_count++;
		pthread_mutex_unlock(&g_mutex);
	}
	//printf("ThreadID: %d Count=%d\n", *tid, g_thcount[*tid]);
    
    pthread_exit(NULL);
}


//------------------------------//
//   River flows in summer
//------------------------------//
