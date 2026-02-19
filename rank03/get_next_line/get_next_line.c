/*
Assignment name: broken_gnl
expcteted files: get_next_line.c get_next_line.h
allowed: read, free, malloc

Repair the function get_next_line in this file. It's prototype should look like this:
char *get_next_line(int	fd);

You might need to repair other functions as well. Your function must return a line that 
has been read from the file descriptor, passed as a parameter.
A 'line that has been read' is defined as a succesion of 0 to n characters ending with
'\n' or with EOF.
The line should be teruned including the '\n' if there is one at the end of the line 
that has been read.
When you reach EOF, you must store the current buffer in a *char and return it.
If the buffer is empty, you must return NULL.
In case of an error, return NULL.
If not returning NULL, the pointer should be freeable.
Your programm will be compiled with the flag -D BUFFER_SIZE = xx which be used as the 
buffer size for the read calls in your functions.
Vour function must be free of memory leaks.
When you reach EOF your function should not keep any memory allocated with malloc
except for the line that has to be returned.
Calling your function in a loop will allow you to read the tet available on a fd
one line at a time ntil the end of the tet regardless of the size of the text or any
of its lines.
Ensure that your function behaves correctyl when reading from a file from the standart
output, form a bla bla etc.
No call to another function will be done on the file descriptor between 2 calls of gnl.
binary file is undefined.
*/

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char *ft_strchr(char *s, int c)
{
	int i = 0;

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
	while (n-- > 0)
		((char *)dest)[n] = ((char *)src)[n];

	
	return dest;
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
	tmp [size1 + size2] = '\0';
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
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
char	*get_next_line(int fd)
{
	/* Static read buffer: persists between calls, holds leftover from last line */
	static char buffer[BUFFER_SIZE + 1] = "";
	/* Stash: accumulated string for current line (grows with each read until we see \n) */
	char	*stash = NULL;
	/* Pointer to \n in stash, or NULL; loop runs while we haven't found one */
	char	*newline = NULL;
	/* The line we will return (malloc'd, or stash on EOF) */
	char	*line;
	size_t	line_len;
	size_t	rest_len;
	ssize_t	bytes_read;

	/* Read until we have a newline in stash (then newline != NULL) or hit EOF */
	while (!newline)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)	/* read error */
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';	/* null-terminate so buffer is a string */
		if (bytes_read == 0)		/* EOF: no more data, exit loop */
			break ;
		if (!str_append_str(&stash, buffer))	/* append this chunk to stash */
			return (NULL);
		newline = ft_strchr(stash, '\n');	/* if \n in stash, loop exits */
	}
	/* No data to return (empty file or nothing left) */
	if (!stash || !stash[0])
	{
		free(stash);
		return (NULL);
	}
	newline = ft_strchr(stash, '\n');
	
	if (newline)
	{
		/* We found a full line: from start of stash up to and including \n */
		line_len = newline - stash + 1;
		line = malloc(line_len + 1);
		if (!line)
		{
			free(stash);
			return (NULL);
		}
		ft_memcpy(line, stash, line_len);
		line[line_len] = '\0';
		/* Rest = everything after the line; save it in buffer for next call */
		rest_len = ft_strlen(stash) - line_len;
		ft_memcpy(buffer, stash + line_len, rest_len + 1);
		free(stash);
		return (line);
	}
	/* EOF with no \n: return the last "line" (stash), clear buffer for next call */
	line = stash;
	buffer[0] = '\0';
	return (line);
}
