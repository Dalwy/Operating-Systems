#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TIMES 10
#define CAPACITY 5
#define ITEMSIZE 10

void *Entry_A();
void *Entry_B();


/*
 * Main: Creates the two threads. (A + B) and joins them then runs them at the same time.
 */
int main()
{
    pthread_t tidA;
    pthread_t tidB;

    pthread_create(&tidA, NULL, (void *(*)(void *))Entry_A, NULL);
    pthread_create(&tidB, NULL, (void *(*)(void *))Entry_B, NULL );
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    pthread_exit(0);

}
/*
 * Entry_A And Entry_B are two functions that will print out the desired lines from the example text
 */
void *Entry_A()
{

    int i,j;
    for(j = 0; j <= TIMES; j++)
    {

        for (i = 0; i < CAPACITY; i++)
        {
            printf("%d: AAAAAAAAAA \n", j);
        }
        printf("\n");
//        sleep(5);
    }
    return NULL;

}

void *Entry_B()
{
    int i,j;
    for(j = 0; j < TIMES; j++)
    {
        for (i = 0; i <= CAPACITY; i++)
        {
            printf("%d: BBBBBBBBBB\n", j+1);
        }
        printf("\n");
//        sleep(5);
    }
    return NULL;


}


