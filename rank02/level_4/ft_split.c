/*
Assignment name  : ft_split
Expected files   : ft_split.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);

*/

#include <stdlib.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	countwords(char *s)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			wordcount++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (wordcount);
}

char	*word(char *s)
{
	int		i;
	char	*new_s;

	i = 0;
	while (s[i] && !is_space(s[i]))
		i++;
	new_s = malloc((i + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0; // reset cause we use it for copying the word
	while (s[i] && !is_space(s[i]))
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

void	free_split(char **split, int up_to)
{
	int	i;

	i = 0;
	while (i < up_to)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char *str)
{
	int		i;
	int		wordcount;
	char	**new_s;

	if (!str)
		return (NULL);
	new_s = malloc((countwords(str) + 1) * sizeof(char *));
	if (!new_s)
		return (NULL);
	i = 0;
	wordcount = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			i++;
		else
		{
			new_s[wordcount] = word(str + i);
			if (!new_s[wordcount])
			{
				free_split(new_s, wordcount);
				return (NULL);
			}
			wordcount++;
			while (str[i] && !is_space(str[i]))
				i++;
		}
	}
	new_s[wordcount] = NULL;
	return (new_s);
}