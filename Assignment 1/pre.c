#include <stdio.h>
#define MIN_STATE 10
#define POP_SIZE 10

/*
 * Create a character array for the States.
 * Create a variable for population size.
 * While the States and population do not equal to the EOF (ctrl -D), read in keyboard input.
 * If the population of a state is greater than 10 then save it to output later.
 */

struct pre
{
    char State[MIN_STATE];
    int population_size;
};
int main()
{
   struct pre temp[MIN_STATE];
   struct pre population;
   int count = 0;
   while(scanf("%s %d", population.State, &population.population_size) != EOF && count != 10)
   {
       if(population.population_size >= POP_SIZE) {
           temp[count] = population;
       }
       count++;
   }
   int i;
   for(i = 0; i < count; i++)
       printf("%s\n", temp[i].State);
    return 0;
}
