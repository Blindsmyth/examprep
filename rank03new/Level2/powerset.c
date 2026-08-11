#include <stdlib.h>
#include <stdio.h>

int sum_set(int *set, int size)
{
	int i = 0;
	int sum = 0;
	while (i < size)
	{
		sum += set[i];
		i++;
	}
	return (sum);
}

void	print_set(int *set, int size)
{
	int i = 0;
	while (i < size)
	{
		printf("%d", set[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
}

void powerset(int *set, int size, char **argv, int start, int sum)
{
	int i = start;

	if (sum_set(set, size) == sum) // no size != 0 because empty set is still valid set
	{
		print_set(set, size);
		printf("\n");
	}
	while (argv[i])
	{
		set[size] = atoi(argv[i]);
		powerset(set, size + 1, argv, i + 1, sum);
		i++;
	}
}

int main(int argc, char **argv)
{
	int sum;

	if (argc < 3)          // validated BEFORE declaring the VLA below
		return (1);
	int set[argc - 2];
	sum = atoi(argv[1]);
	powerset(set, 0, argv, 2, sum);
	return (0);
}
