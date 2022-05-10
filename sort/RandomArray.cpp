
//------------------------------//
//   Coded by 番茄
//   @summer studio
//------------------------------//


#include <unistd.h>   // POSIX SysCall (Unix,Linux,masOS)
#include <stdlib.h>   // standard library of C
#include <stdio.h>

#define MAXSIZE   1000000
#define GAP       100000

using namespace std;


int *gp_rand_array = NULL;

int main(int argc, char **argv, char *env[])
{
    gp_rand_array = (int *) malloc (MAXSIZE * sizeof(int));
    if( gp_rand_array == NULL )
    {
        perror("malloc() failed \n");
		exit(EXIT_FAILURE);
    }

    // as memset
    for(int i=0; i<MAXSIZE; i++)
        gp_rand_array[i] = 0;

    // generate random array
    for(int j=1; j<=MAXSIZE; j++)
    {
        int pos = 0;
        while(1)
        {
            pos = rand() % MAXSIZE;
            if(gp_rand_array[pos] != 0)
                continue;
            else
            {
                gp_rand_array[pos] = j;

                if( j % GAP == 0)
                    printf("# %d POS: %d\n", j, pos);

                break;
            }
        }
    }   

    return 0;
}

//------------------------------//
//   River flows in summer
//------------------------------//
