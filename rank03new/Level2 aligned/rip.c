#include <stdio.h>

static char	*str;
static int	len;

static int	ft_strlen(char *s)
{
	int	i = 0;

	while (s[i])
		i++;
	return (i);
}

static int	min_remove(char *s)
{
	int	i = 0;
	int	open = 0;
	int	close = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

static int	is_balanced(char *s)
{
	int	i = 0;
	int	balance = 0;

	while (s[i])
	{
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')')
			balance--;
		if (balance < 0)
			return (0);
		i++;
	}
	return (balance == 0);
}

static void	print_sol(void)
{
	puts(str);
}

static void	solve(int idx, int to_remove)
{
	int		i;
	char	tmp;

	if (to_remove == 0)
	{
		if (is_balanced(str))
			print_sol();
		return ;
	}
	i = idx;
	while (i < len)
	{
		tmp = str[i];
		str[i] = ' ';			/* remove one bracket*/
		solve(i + 1, to_remove - 1);	/* recurse */
		str[i] = tmp;			/* undo */
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	removes;

	if (argc != 2 || !argv[1][0])
		return (1);
	str = argv[1];
	len = ft_strlen(str);
	removes = min_remove(str);
	if (removes == 0)
	{
		print_sol();
		return (0);
	}
	solve(0, removes);
	return (0);
}
