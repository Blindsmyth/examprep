#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *ft_strchr(char *s, int c)
{
	int i = 0;

	if (!s)
		return NULL;
	
	while (s[i])
	{
		if(s[i] == c)
			return s + i;
		i++;
	}
	return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (n == 0)
		return (dest);
	while (n-- > 0)
		((char *)dest)[n] = ((const char *)src)[n];
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t i = 0;

	if (!s)
		return (0);
	
	while (s[i])
		{
			i++;
		}
	return i;
}

int	str_append(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
    if(!tmp)
        return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
    tmp [size1 + size2] = '\0';
	free (*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append(s1, s2, ft_strlen(s2)));
}
/*
void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
	{
	size_t i = ft_strlen((char *)src) - 1;

	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	}
	return dest;
}
*/


char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1] = "";

    char    *stash = NULL;
    char    *line = NULL;
    char    *newline = NULL;

    ssize_t bytes_read;
    ssize_t total_read = 0;
    size_t  line_len;
    size_t  rest_len;

    if (BUFFER_SIZE < 1)
    {
        free(stash);
        return (NULL);
    }

    if (fd < 0)
    {
        free(stash);
        return (NULL);
    }

    str_append_str(&stash, buffer);

    while (!newline)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);

        if (bytes_read == -1)
        {
            free(stash);
            return (NULL);
        }

        if (bytes_read == 0)
            break;

        buffer[bytes_read] = '\0';

        str_append_str(&stash, buffer);

        /* error check */

        newline = ft_strchr(stash, '\n');

        total_read += bytes_read;
    }

    if (newline)
    {
        line_len = newline - stash;

        line = malloc(line_len + 1);
        if (!line)
        {
            free(stash);
            return (NULL);
        }

        ft_memcpy(line, stash, line_len);

        rest_len = ft_strlen(stash) - line_len;

        ft_memcpy(buffer, newline + 1, rest_len);

        buffer[rest_len] = '\0';

        return (line);
    }
    free(stash);
    return (NULL);
}