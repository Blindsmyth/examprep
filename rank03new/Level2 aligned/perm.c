#include <unistd.h>

static char	*str;
static int	len;
static char	*result;
static int	*used;

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	sort_string(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (s[i] > s[j])
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sol(void)
{
	write(1, result, len);
	write(1, "\n", 1);
}

static void	solve(int idx)
{
	int	i;

	if (idx == len)
	{
		print_sol();
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])			/* ok */
		{
			used[i] = 1;
			result[idx] = str[i];	/* place */
			solve(idx + 1);		/* recurse */
			used[i] = 0;		/* undo */
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		return (1);
	str = argv[1];
	len = ft_strlen(str);
	char	res[len + 1];
	int		u[len];

	result = res;
	used = u;
	i = 0;
	while (i < len)
	{
		used[i] = 0;
		i++;
	}
	result[len] = '\0';
	sort_string(str);
	solve(0);
	return (0);
}
