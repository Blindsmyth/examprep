/*
 * powerset with globals (same style as n_queens.c).
 *
 * Globals hold shared state; recursion only passes what changes per call:
 *   size  = how many numbers are in the current subset
 *   start = first index in nums[] we may still pick
 *
 * Example: ./powerset 5 1 2 3 4 5
 *   1 4
 *   2 3
 *   5
 */

#include <stdlib.h>
#include <stdio.h>

int	*set;		/* subset being built (like queen_col) */
int	*nums;		/* all input numbers (argv[2..] converted once) */
int	n_nums;		/* how many numbers */
int	target;		/* sum we want (like board_size is "n") */

int	sum_set(int size)
{
	int	i = 0;
	int	sum = 0;

	while (i < size)
	{
		sum += set[i];
		i++;
	}
	return (sum);
}

void	print_set(int size)
{
	int	i = 0;

	while (i < size)
	{
		printf("%d", set[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	printf("\n");
}

/*
 * Only size and start change between recursive calls.
 * Everything else is global — same idea as solve(row) in n_queens.
 */
void	powerset(int size, int start)
{
	int	i = start;

	if (sum_set(size) == target)
		print_set(size);
	while (i < n_nums)
	{
		set[size] = nums[i];
		powerset(size + 1, i + 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 3)
		return (1);
	target = atoi(argv[1]);
	n_nums = argc - 2;
	set = malloc(sizeof(int) * n_nums);
	nums = malloc(sizeof(int) * n_nums);
	if (!set || !nums)
		return (1);
	i = 0;
	while (i < n_nums)
	{
		nums[i] = atoi(argv[i + 2]);
		i++;
	}
	powerset(0, 0);		/* empty subset, start at first number */
	free(set);
	free(nums);
	return (0);
}
