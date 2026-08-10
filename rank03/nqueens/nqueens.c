/* Assignment name : n_queens
Expected files : *.c *.h
Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

Write a program that prints all n-queens solutions.
Format: row index per column, 0-based, e.g. "1 3 0 2"
*/

/*
 * Same idea as bin_naruto — fill one slot, recurse to the next, print when full.
 *
 * bin_naruto:  s[idx] = '0' or '1'          → try every bit
 * n_queens:    board[col] = 0 .. n-1 (row)  → try every row in this column
 *
 * Difference: not every choice is allowed. Before recursing we ask ok().
 * That pruning is the "backtracking" part — bad branches die early.
 *
 * board[col] = row  means: queen in column `col` sits on row `row`.
 *
 * $> ./nqueens 4
 * 1 3 0 2
 * 2 0 3 1
 *
 * First line: col0→row1, col1→row3, col2→row0, col3→row2
 */

#include <stdio.h>
#include <stdlib.h>

static int	n;
static int	*board; /* like `s` in bin_naruto: one value per column */

/* Can we place a queen at (col, row) given queens already in columns 0..col-1? */
static int	ok(int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		/* same row, or same diagonal (row distance == col distance) */
		if (board[i] == row
			|| board[i] - row == col - i
			|| row - board[i] == col - i)
			return (0);
		i++;
	}
	return (1);
}

/*
 * solve(col)  ≈  biNarutoHelper(idx, ...)
 *
 *   idx / col     = which slot we fill now
 *   digits / n    = how many slots until we're done
 *   s / board     = the partial answer being built
 */
static void	solve(int col)
{
	int	row;

	/* BASE CASE — like `if (idx == digits) printf("%s\n", s);`
	 * Every column has a queen → print this solution, then return
	 * (backtrack to try other choices higher up). */
	if (col == n)
	{
		row = 0;
		while (row < n)
		{
			fprintf(stdout, "%d", board[row]);
			if (row + 1 < n)
				fprintf(stdout, " ");
			row++;
		}
		fprintf(stdout, "\n");
		return ;
	}

	/* RECURSION — like trying '0' then '1' at s[idx].
	 * Here the "alphabet" is rows 0..n-1, but only if ok().
	 *
	 *   board[col] = row;   // place choice (like s[idx] = '0')
	 *   solve(col + 1);     // fill the rest (like helper(idx + 1, ...))
	 *
	 * No explicit "undo": next loop iteration overwrites board[col].
	 * When this call returns, the caller tries its next choice. */
	row = 0;
	while (row < n)
	{
		if (ok(col, row))
		{
			board[col] = row;
			solve(col + 1);
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
	/* like calloc(digits + 1) for the bit string — here n ints, one per column */
	board = calloc(n, sizeof(int));
	if (!board)
		return (1);
	solve(0); /* start at column 0, like helper(0, digits, s) */
	free(board);
	return (0);
}
