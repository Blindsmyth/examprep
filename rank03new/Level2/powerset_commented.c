/*
 * powerset: print every subset of argv[2..] whose values sum to argv[1].
 *
 * Backtracking, same idea as n-queens:
 *   place a number in the current subset → recurse → try the next number.
 * start = i + 1 so each argv slot is used at most once
 * (subsets, not permutations: {1,2} not also {2,1}).
 *
 * Example: ./powerset 5 1 2 3 4 5
 *   1 4
 *   2 3
 *   5
 */

#include <stdlib.h>
#include <stdio.h>

/* Sum of the current subset set[0 .. size-1]. */
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

/* Print the current subset, spaces between numbers, no trailing space. */
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

/*
 * set   = subset being built
 * size  = how many numbers are already in set
 * start = first argv index we are allowed to pick next (skip already-used ones)
 * sum   = target
 * argv  = last (ints first — easier to remember)
 *
 * At every call: if current subset hits the target, print it,
 * then try appending each remaining number and recurse.
 */
void powerset(int *set, int size, int start, int sum, char **argv)
{
	int i = start;

	/* Empty subset is valid if target is 0 — do not require size != 0. */
	if (sum_set(set, size) == sum)
	{
		print_set(set, size); 
		printf("\n");
	}
	/* For each remaining number: append it, recurse, then try the next.
	 * No explicit undo: next set[size] = ... overwrites this slot. */
	while (argv[i])
	{
		set[size] = atoi(argv[i]);
		powerset(set, size + 1, i + 1, sum, argv);
		i++;
	}
}

int main(int argc, char **argv)
{
	int sum;

	/* Need at least program name, target, and one number? Subject often
	 * allows no numbers (only target). argc < 2 would be safer for that;
	 * this version requires argc >= 3. */
	if (argc < 3)
		return (1);
	int set[argc - 2];		/* room for every number in argv[2..] */
	sum = atoi(argv[1]);
	powerset(set, 0, 2, sum, argv);	/* empty subset, first number at argv[2] */
	return (0);
}



