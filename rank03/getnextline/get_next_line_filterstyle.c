/*
 * get_next_line — filter-style version.
 * Same variable names and pattern as filter.c: buffer (stack), result (accumulated),
 * temp (realloc), total_read, bytes_current. Only allowed: read, free, malloc.
 */

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

/* Find first '\n' in buf[0..len); return index or len if not found */
static size_t	find_newline(char *buf, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && buf[i] != '\n')
		i++;
	return (i);
}

/* Copy n bytes from src to dst (no overlap). */
static void	copy_bytes(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	*result = NULL;
	static size_t	total_read = 0;
	char		buffer[BUFFER_SIZE];
	char		*temp;
	char		*line;
	size_t		line_len;
	size_t		rest_len;
	ssize_t		bytes_current;
	size_t		newline_i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	/* Read until we have a newline or EOF */
	while (1)
	{
		newline_i = find_newline(result, total_read);
		if (newline_i < total_read)
			break ;
		bytes_current = read(fd, buffer, BUFFER_SIZE);
		if (bytes_current < 0)
		{
			free(result);
			result = NULL;
			total_read = 0;
			return (NULL);
		}
		if (bytes_current == 0)
			break ;
		temp = realloc(result, total_read + bytes_current + 1);
		if (!temp)
		{
			free(result);
			result = NULL;
			total_read = 0;
			return (NULL);
		}
		result = temp;
		copy_bytes(result + total_read, buffer, bytes_current);
		total_read += bytes_current;
		result[total_read] = '\0';
	}

	/* No data to return */
	if (!result || total_read == 0)
	{
		free(result);
		result = NULL;
		total_read = 0;
		return (NULL);
	}

	newline_i = find_newline(result, total_read);
	if (newline_i < total_read)
		line_len = newline_i + 1;
	else
		line_len = total_read;

	line = malloc(line_len + 1);
	if (!line)
	{
		free(result);
		result = NULL;
		total_read = 0;
		return (NULL);
	}
	copy_bytes(line, result, line_len);
	line[line_len] = '\0';

	rest_len = total_read - line_len;
	if (rest_len == 0)
	{
		free(result);
		result = NULL;
		total_read = 0;
		return (line);
	}

	temp = malloc(rest_len + 1);
	if (!temp)
	{
		free(line);
		free(result);
		result = NULL;
		total_read = 0;
		return (NULL);
	}
	copy_bytes(temp, result + line_len, rest_len);
	temp[rest_len] = '\0';
	free(result);
	result = temp;
	total_read = rest_len;
	return (line);
}
