#include <stdio.h>
#include <stdlib.h>

int sum_set(int *set, int size)
{
    int i = 0;
    int sum = 0;
    while(i < size)
    {
        sum += set[i];
        i++;
    }
    return (sum);
}

void    print_set (int *set, int size)
{
    int i = 0;

    while(i < size)
    {
        printf("%d", set[i]);
        if (i < size - 1)
            printf(" ");
        i++;
    }
}


void powerset (int *set, int size, int start, int sum, char **argv)
{
    int i = start;
    if (sum_set(set, size) == sum)
        {
            print_set(set, size);
		    printf("\n");
        }
    
    while (argv[i])
    {
        set[size] = atoi(argv[i]);
        /* i + 1, not start + 1: skip past the number you just took */
        powerset(set, size + 1, i + 1, sum, argv);
        i++;
    }

}


int main (int argc, char **argv)
{
    int sum;
    if (argc < 3)
        return 1;

    int set[argc - 2];
    sum = atoi(argv[1]);
    /* start at 2: argv[0]=prog, argv[1]=target, numbers from argv[2] */
    powerset(set, 0, 2, sum, argv);
    return 0;
}