#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

/*
 * Exam-friendly implementation that reuses helper functions heavily.
 * Focus: fix helpers first, then keep get_next_line logic simple.
 */

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == '\0')
		return (s + i);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	str_append(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size1 + size2 + 1);
	if (!tmp)
		return (0);
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	if (s2 && size2 > 0)
		ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	i = n;
	while (i > 0)
	{
		i--;
		((char *)dest)[i] = ((const char *)src)[i];
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*stash;
	char		*newline;
	char		*line;
	ssize_t		bytes_read;
	size_t		line_len;
	size_t		rest_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = NULL;
	newline = ft_strchr(buffer, '\n');
	while (!newline)
	{
		if (!str_append_str(&stash, buffer))
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			buffer[0] = '\0';
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		newline = ft_strchr(buffer, '\n');
	}
	if (!str_append_str(&stash, buffer))
		return (NULL);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		return (NULL);
	}
	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		buffer[0] = '\0';
		return (stash);
	}
	line_len = (size_t)(newline - stash) + 1;
	line = malloc(line_len + 1);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	ft_memcpy(line, stash, line_len);
	line[line_len] = '\0';
	rest_len = ft_strlen(stash + line_len);
	ft_memmove(buffer, stash + line_len, rest_len);
	buffer[rest_len] = '\0';
	free(stash);
	return (line);
}
