#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TIMES 10
#define CAPACITY 5
#define ITEMSIZE 10

void *Entry_A();
void *Entry_B();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*
 * Main: Creates and Joins the two threads and runs them at the same time
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
 * Entry_A and Entry_B will output the desired output from the example except give Thread A the Priority with the mutex
 * locks and unlocks.
 */
void *Entry_A()
{

    int i,j;
    for(j = 0; j <= TIMES; j++)
    {
        pthread_mutex_lock(&mutex);
        for (i = 0; i < CAPACITY; i++)
        {
            printf("%d: AAAAAAAAAA \n", j);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    return NULL;

}

void *Entry_B()
{
    int i,j;
    for(j = 0; j < TIMES; j++)
    {
        pthread_mutex_lock(&mutex);
        for (i = 0; i <= CAPACITY; i++)
        {
            printf("%d: BBBBBBBBBB\n", j+1);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    return NULL;


}


