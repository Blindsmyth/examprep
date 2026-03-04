/*
Assignment name : rip
Expected files : *.c *.h
Allowed functions: puts, write
• -------------------------------------------------------------------------------

Write a program that will take as argument a string containing only parenthesis.
if the parenthesis are unbalanced
your program shall remove the minimum number of parentheses for the expression to be balanced.
By removing we mean replacing by spaces.
You will then print all the solutions (can be more than one).

The order of the solutions is not important.

For example this should work:
$> ./rip '(()' | cat -e
()$
( )$
$> ./rip '((()()())())' | cat -e
((()()())())$
$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$
$> ./rip '(()(()(' | cat -e
(() ) $
( )( ) $
( ) () $
 ()( ) $

*/

#include <unistd.h>

#define MAX_LEN  256
#define MAX_SOL  1024

static char	g_buf[MAX_LEN + 1];
static char	g_sols[MAX_SOL][MAX_LEN + 1];
static int	g_nsol;

static int	ft_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	same(int len)
{
	int	i;
	int	j;

	j = 0;
	while (j < g_nsol)
	{
		i = 0;
		while (i < len && g_buf[i] == g_sols[j][i])
			i++;
		if (i == len)
			return (1);
		j++;
	}
	return (0);
}

static void	add_sol(int len)
{
	int	i;

	if (same(len))
		return;
	i = 0;
	while (i < len)
	{
		g_sols[g_nsol][i] = g_buf[i];
		i++;
	}
	g_sols[g_nsol][len] = '\0';
	g_nsol++;
	i = 0;
	while (i < len)
		write(1, &g_buf[i++], 1);
	write(1, "\n", 1);
}

static void	backtrack(char *str, int i, int len, int open, int ro, int rc, int L, int R)
{
	char	c;

	if (i == len)
	{
		if (open == 0 && ro == L && rc == R)
			add_sol(len);
		return ;
	}
	c = str[i];
	if (c == '(')
	{
		backtrack(str, i + 1, len, open + 1, ro, rc, L, R);
		if (ro < L)
		{
			g_buf[i] = ' ';
			backtrack(str, i + 1, len, open, ro + 1, rc, L, R);
			g_buf[i] = '(';
		}
	}
	else if (c == ')')
	{
		if (open > 0)
			backtrack(str, i + 1, len, open - 1, ro, rc, L, R);
		if (rc < R)
		{
			g_buf[i] = ' ';
			backtrack(str, i + 1, len, open, ro, rc + 1, L, R);
			g_buf[i] = ')';
		}
	}
}

int	main(int ac, char **av)
{
	char	*str;
	int		len;
	int		i;
	int		open;
	int		L;
	int		R;

	if (ac != 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	str = av[1];
	len = ft_len(str);
	if (len > MAX_LEN)
		return (1);
	open = 0;
	R = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')' && open > 0)
			open--;
		else if (str[i] == ')')
			R++;
		i++;
	}
	L = open;
	if (L == 0 && R == 0)
	{
		i = 0;
		while (i < len)
			write(1, &str[i++], 1);
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	while (i < len)
	{
		g_buf[i] = str[i];
		i++;
	}
	g_buf[len] = '\0';
	g_nsol = 0;
	backtrack(str, 0, len, 0, 0, 0, L, R);
	return (0);
}
