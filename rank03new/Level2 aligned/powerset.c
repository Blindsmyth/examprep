#include <stdlib.h>
#include <stdio.h>

static int	*set;
static int	target;
static char	**av;

static int	sum_set(int idx)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < idx)
	{
		sum += set[i];
		i++;
	}
	return (sum);
}

static void	print_sol(int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		printf("%d", set[i]);
		if (i + 1 < idx)
			printf(" ");
		i++;
	}
	printf("\n");
}

static void	solve(int idx, int start)
{
	int	i;

	/* print on the way — do not return; short subsets can be solutions */
	if (sum_set(idx) == target)
		print_sol(idx);
	i = start;
	while (av[i])
	{
		set[idx] = atoi(av[i]);	/* place */
		solve(idx + 1, i + 1);		/* recurse; start = i + 1 */
		/* undo: next i overwrites set[idx] */
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	int	buf[argc - 2];

	set = buf;
	target = atoi(argv[1]);
	av = argv;
	solve(0, 2);
	return (0);
}
