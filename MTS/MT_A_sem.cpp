
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>     // POSIX API (Unix,Linux,masOS)
#include <pthread.h>    // POSIX Thread
#include <stdlib.h>     // C Standard Library
#include <stdio.h>
#include <semaphore.h>

#define THSCALE   100

using namespace std;


// Thread Function Declaration
void *Thread_Func(void *args);

sem_t g_sem;
int g_count;
int g_tid[THSCALE];
int g_thcount[THSCALE];


int main(int argc, char **argv, char *env[])
{    
    pthread_t tid[THSCALE];
    //void *status;

	// int sem_init(sem_t *sem, int pshared, unsigned int value);
	// pshared 指明信号量的类型
	// 不为0时此信号量在进程间共享
	// 否则只能为当前进程的所有线程共享
	int res = sem_init(&g_sem, 0, 1);
	if(res != 0)
	{
		perror("sem_init() failed \n");
		exit(EXIT_FAILURE);
	}
	else
		printf("sem_init() suceed \n");

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

	res = sem_destroy(&g_sem);
	if(res == 0)
		printf("sem_destroy() suceed \n");

    printf("Process #%d FINISHED \n", getpid());
    exit(EXIT_SUCCESS);
}

void *Thread_Func(void *args)
{
	int *tid = (int *)args;
    for (int i = 0; i < 10000; i++)
	{
		g_thcount[*tid]++;
		sem_wait(&g_sem);
		g_count++;
		sem_post(&g_sem);
	}
	//printf("ThreadID: %d Count=%d\n", *tid, g_thcount[*tid]);
    
    pthread_exit(NULL);
}


//------------------------------//
//   River flows in summer
//------------------------------//
