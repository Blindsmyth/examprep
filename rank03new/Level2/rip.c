/*
// for rip.h

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

int	min_remove(char *str)
{
	int	i;
	int	open;
	int	close;

	i = 0;
	open = 0;
	close = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
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
		if (balance < 0)
			return (0);
		i++;
	}
	return (balance == 0);
}

void	solve(char *str, int len, int idx, int to_remove)
{
	int	i;
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
		tmp = str[i];
		str[i] = ' ';
		solve(str, len, i + 1, to_remove - 1);
		str[i] = tmp;
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
	if (removes == 0)
	{
		puts(argv[1]);
		return (0);
	}
	solve(argv[1], len, 0, removes);
	return (0);
}
