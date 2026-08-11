#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

int *queen_col;
int	board_size;

void	print_sol(void)
{
	int	i = 0;

	while (i < board_size)
	{
		fprintf(stdout, "%d", queen_col[i]);
		if (i < board_size - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

bool	is_safe(int col, int row)
{
	int i = 0;

	while (i < row)
	{
		if (queen_col[i] == col)
			return (false);
		if (ft_abs(queen_col[i] - col) == ft_abs(i - row))
			return (false);
		i++;
	}
	return (true);
}

void	solve(int row)
{
	int	col = 0;

	if (row == board_size)
	{
		print_sol();
		return ;
	}
	while (col < board_size)
	{
		if (is_safe(col, row))
		{
			queen_col[row] = col;
			solve(row + 1);
		}
		col++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)                 // n <= 3 is NOT an error, don't special-case it
		return (1);
	board_size = atoi(av[1]);
	queen_col = malloc(sizeof(int) * board_size);
	if (!queen_col)
		return (1);
	solve(0);
	free(queen_col);
	return (0);
}
