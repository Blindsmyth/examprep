#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	sort(char *str, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	reverse(char *str, int l, int r)
{
	char	tmp;

	while (l < r)
	{
		tmp = str[l];
		str[l] = str[r];
		str[r] = tmp;
		l++;
		r--;
	}
}

int	next_permutation(char *str, int len)
{
	int	i;
	int	j;

	i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	reverse(str, i + 1, len - 1);
	j = i + 1;
	while (str[j] <= str[i])
		j++;
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return (1);
}

int	main(int ac, char **av)
{
	char	*str;
	int		len;

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	str = malloc(len + 1);
	if (!str)
		return (1);
	ft_strcpy(str, av[1]);
	sort(str, len);
	do
	{
		write(1, str, len);
		write(1, "\n", 1);
	} while (next_permutation(str, len));
	free(str);
	return (0);
}
