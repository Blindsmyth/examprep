/*
 * rip: make a parentheses string balanced by replacing the MINIMUM
 * number of '(' / ')' with spaces, then print ALL such solutions.
 *
 * Plan (3 steps):
 *   1) min_remove  — how many must go?
 *   2) solve       — try blanking exactly that many chars (backtracking)
 *   3) is_balanced — if what's left is valid, print it
 *
 * Example: ./rip '()())()'
 *   ()() ()
 *   ()( )()
 *   ( ())()
 *
 * Needs rip.h (prototype for solve) or uncomment the header block below.
 */

/*
#ifndef RIP_H
# define RIP_H
# include <unistd.h>
# include <stdio.h>
void	solve(char *str, int len, int idx, int to_remove);
#endif
*/

#include "rip.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
 * Count the minimum removals.
 * open  = unmatched '(' so far
 * close = ')' that had no '(' to pair with (must remove)
 *
 * On ')':
 *   if open > 0 → cancel one waiting '(' (a valid pair)
 *   else        → this ')' is excess → close++
 * Leftover open at the end = extra '(' that must also go.
 * Return open + close.
 *
 * "(()" → open ends at 1 → remove 1
 * "())" → close ends at 1 → remove 1
 */
int	min_remove(char *str)
{
	int	i;
	int	open;
	int	close;

	i = 0;
	open = 0;
	close = 0;
	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--;		/* matched with a previous '(' */
			else
				close++;	/* no '(' waiting → must remove this ')' */
		}
		i++;
	}
	return (open + close);
}

/*
 * Valid parentheses string?
 * balance never goes negative (no ')' before a '('),
 * and ends at 0 (every '(' closed).
 * Spaces are ignored (they are "removed" chars).
 */
int	is_balanced(char *str)
{
	int	i;
	int	balance;

	i = 0;
	balance = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
			balance--;
		if (balance < 0)		/* too many ')' at this point */
			return (0);
		i++;
	}
	return (balance == 0);		/* leftover '(' → not balanced */
}

/*
 * Backtracking: replace exactly to_remove parentheses with ' '.
 *
 * idx      = first index we may still blank (avoids duplicate solutions
 *            from blanking the same set in different order)
 * to_remove = how many blanks we still need to place
 *
 * Base case: nothing left to remove → if balanced, print.
 * Else: try blanking each position i >= idx, recurse, then undo.
 */
void	solve(char *str, int len, int idx, int to_remove)
{
	int		i;
	char	tmp;

	if (to_remove == 0)
	{
		if (is_balanced(str))
			puts(str);
		return ;
	}
	i = idx;
	while (i < len)
	{
		tmp = str[i];			/* save original '(' or ')' */
		str[i] = ' ';			/* "remove" it */
		solve(str, len, i + 1, to_remove - 1);
		str[i] = tmp;			/* undo — try next position */
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	len;
	int	removes;

	if (argc != 2 || !argv[1][0])
		return (1);
	len = ft_strlen(argv[1]);
	removes = min_remove(argv[1]);
	if (removes == 0)			/* already balanced — just print */
	{
		puts(argv[1]);
		return (0);
	}
	solve(argv[1], len, 0, removes);
	return (0);
}
