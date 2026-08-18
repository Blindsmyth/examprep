#include <stdio.h>
#include <stdlib.h>

static int	n;
static int	*board;

static void	print_sol(void)
{
	int	i;

	i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i + 1 < n)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}


static int	ok(int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (board[i] == row
			|| board[i] - row == col - i
			|| row - board[i] == col - i)
			return (0);
		i++;
	}
	return (1);
}

static void	solve(int col)
{
	int	row;

	if (col == n)
	{
		print_sol();
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (ok(col, row))
		{
			board[col] = row;	/* place */
			solve(col + 1);		/* recurse */
			/* undo: next row overwrites board[col] */
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	if (n <= 0)
		return (0);
	int	buf[n];

	board = buf;
	solve(0);
	return (0);
}
