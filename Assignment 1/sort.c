#include <stdio.h>
#include <string.h>
#define SIZE 150

/*
 * Read in a list of states, and sort them in alphabetical order.
 * No more than 10 states. And terminates when it hits EOF.
 */

/*
 * Struct for an array to hold the states.
 */
struct sort
{
    char state[SIZE];
};
int main()
{
    /*
     * Temp variable to hold the
     */
    struct sort name[SIZE];
    struct sort temp;
    char array[2];
    int i, x;
    int count = 0;
    while(scanf("%s", temp.state) != EOF && count != 10)
    {
        strcpy(name[count].state, temp.state);
        count++;
    }
    /*
     * Bubble sort to sort the states in Alphabetical order.
     */
    for(i = 0; i < count; i++) {
        for (x = i; x < count; x++) {
            if (strcmp(name[i].state, name[x].state) > 0) {
                strcpy(array, name[i].state);
                strcpy(name[i].state, name[x].state);
                strcpy(name[x].state, array);
            }
        }
    }

    int j;
    for(j = 0; j < count; j++)
        printf("\n%s\n", name[j].state);
}