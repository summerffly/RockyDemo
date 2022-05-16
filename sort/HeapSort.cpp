
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define MAXSIZE   1000000
#define SCALE     50000
#define GAP       100000

using namespace std;


// Global Random Array
int *gp_rand_array = NULL;

int g_rate_param;
long g_cmp_count;
long g_swp_count;
long g_mov_count;

void InitRandomArray();
void ShowSortedArray();


// Heap Adjust
void HeapAdjust(int pos, int end)
{    
    int tmp = gp_rand_array[pos];

    for(int j=pos*2; j<=end; j*=2)
    {
        g_cmp_count++;
        if( j<end && gp_rand_array[j] < gp_rand_array[j+1] )
            j++;
        
        if( tmp >= gp_rand_array[j] )
            break;
        
        g_mov_count++;
        gp_rand_array[pos] = gp_rand_array[j];
        pos = j;
    }

    gp_rand_array[pos] = tmp;
}

// Heap Sort
void *HeapSort_Func(void *args)
{
    g_cmp_count = 0;
    g_swp_count = 0;
    g_mov_count = 0;

    for(int i=MAXSIZE/2; i>0; i--)
    {
        HeapAdjust(i, MAXSIZE);
    }

    for(int i=MAXSIZE; i>1; i--)
    {
        g_swp_count++;
        int tmp = gp_rand_array[i];
        gp_rand_array[i] = gp_rand_array[1];
        gp_rand_array[1] = tmp;

        HeapAdjust(1, i-1);
    }

    printf("[CMP: %5dw][MOV: %5dw][SWP: %5dw]\n", g_cmp_count/10000, g_mov_count/10000, g_swp_count/10000);

    pthread_exit(NULL);
}


/******************************/
/***       MAIN ENTRY       ***/
/******************************/
int main(int argc, char **argv, char *env[])
{
    struct timeval tvl_begin;
    struct timeval tvl_end;
    pthread_t tid_sort;
    void *status;

    InitRandomArray();
    g_swp_count = 0;
    g_cmp_count = 0;

    printf("----------------------------------------\n");
    printf("START %s :)\n", "Heap Sort");
    printf("----------------------------------------\n");
    gettimeofday(&tvl_begin, NULL);

    pthread_create(&tid_sort, NULL, HeapSort_Func, NULL);
    pthread_join(tid_sort, &status);

    gettimeofday(&tvl_end, NULL);
    printf("----------------------------------------\n");
    
    long tgap_us;
    double tgap_ms;
    tgap_us = (tvl_end.tv_sec - tvl_begin.tv_sec) * 1000000 + tvl_end.tv_usec - tvl_begin.tv_usec;
    tgap_ms = (double)tgap_us/1000;
    printf("SortTime: %f ms\n", tgap_ms);
    printf("----------------------------------------\n");

    ShowSortedArray();
    printf("----------------------------------------\n");

    return 0;
}

void InitRandomArray()
{
    gp_rand_array = (int *) malloc ((MAXSIZE+1) * sizeof(int));
    if( gp_rand_array == NULL )
    {
        perror("malloc() failed \n");
		exit(EXIT_FAILURE);
    }

    for(int i=0; i<MAXSIZE+1; i++)
        gp_rand_array[i] = 0;

    for(int j=1; j<=MAXSIZE; j++)
    {
        int pos = 0;
        while(1)
        {
            pos = rand() % MAXSIZE + 1;
            if(gp_rand_array[pos] != 0)
                continue;
            else
            {
                gp_rand_array[pos] = j;
                break;
            }
        }
    }
}

void ShowSortedArray()
{
    printf("POS: %7d # %d \n", 1, gp_rand_array[1]);

    for(int i=1; i<MAXSIZE; i++)
    {
        if( i % GAP == 0 )
            printf("POS: %7d # %d \n", i, gp_rand_array[i]);
    }

    printf("POS: %7d # %d \n", MAXSIZE, gp_rand_array[MAXSIZE]);
}


//------------------------------//
//   River flows in summer
//------------------------------//
