#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

/*
 * Create a reference string of at most 20 random integers.
 * Take in the number of frames.
 * Print out the page replacement as it goes through the reference string and compare the LRU and Optimal Algorithms
 */
#define Pages 6
#define MAX 30

void LRUSolution(int a[], int size, int NumFrames);
void OptimalSolution(int a[], int size, int NumFrames);

int main()
{
    int NumFrames, i;
    printf("Enter the number of frames: ");
    scanf("%d", &NumFrames);
    int a[MAX];
    for(i=0; i< MAX; i++)
        a[i] = rand()%6;
    printf("The Reference string is: ");
    int index = 0;
    for(index; index < MAX; index++)
        printf("%d", a[index]);
    printf("\n");
    printf("========== LRU =========\n");
    LRUSolution(a, MAX, NumFrames);
    printf("========== Optimal =========\n");
    OptimalSolution(a, MAX, NumFrames);
    return 0;
}
/*
 * The LRU Algorithm
 */
void LRUSolution(int a[], int size, int NumFrames)
{
    int i = 0,
    PageFaults = 0,
    index = 0;
    int lru,
    counter;
    int frame[NumFrames];
    bool page[Pages] = {false};
    for(i; i < size; i++)
    {
        if((index < NumFrames) && (!page[a[i]]))
        {
            frame[index++] = a[i];
            page[a[i]] = true;
            PageFaults++;
        }
        if((index >= NumFrames) && (!page[a[i]]))
        {
            counter = 0;
            bool value[Pages] = {false};
            PageFaults++;
            int x;
            for(x = i - 1; ; x--)
            {
                if((counter == NumFrames) || (x < 0))
                    break;
                if((page[a[x]]) && ( !value[a[x]]))
                {
                    lru = a[x];
                    value[a[x]] = true;
                    counter++;
                }
            }
            printf("Number %d is being replaced.\n\n", lru);
            page[lru] = false;
            int y;
            for(y = 0; y < NumFrames; y++)
            {
                if(frame[y] == lru)
                    break;
            }
            frame[y] = a[i];
            page[a[i]] = true;
        }
        int temp = 0;
        for(temp; temp < index; temp++)
            printf("%d", frame[temp]);
        printf("\n");
    }
    int x = MAX - PageFaults;
    printf("\n Number of Page Faults: %d", PageFaults);
    printf("\n Number of Hits: %d\n", x);
}
/*
 * The Optimal algorithm
 */
void OptimalSolution(int a[], int size, int NumFrames)
{
    int i = 0,
    PageFaults = 0,
    index = 0;
    int Optimal,
    counter;
    int frame[NumFrames];
    bool page[Pages] = {false};
    for(i; i < size; i++)
    {
        if((index < NumFrames) && (!page[a[i]]))
        {
            frame[index++] = a[i];
            page[a[i]] = true;
            PageFaults++;
        }
        if((index >= NumFrames) && (!page[a[i]]))
        {
            counter = 0;
            bool value[Pages] = {false};
            PageFaults++;
            int x;
            for(x = i + 1; ; x++)
            {
                if((counter == NumFrames) || (x == size))
                    break;
                if((page[a[x]]) && ( !value[a[x]]))
                {
                    Optimal= a[x];
                    value[a[x]] = true;
                    counter++;
                }
            }
            printf("Number %d is being replaced.\n\n", Optimal);
            page[Optimal] = false;
            int y;
            for(y = 0; y < NumFrames; y++)
            {
                if(frame[y] == Optimal)
                    break;
            }
            frame[y] = a[i];
            page[a[i]] = true;
        }
        int temp = 0;
        for(temp; temp < index; temp++)
            printf("%d", frame[temp]);
        printf("\n");

    }
    int x = MAX - PageFaults;
    printf("\n Number of Page Faults: %d", PageFaults);
    printf("\n Number of Hits: %d \n", x);
}
