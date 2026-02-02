/*
Assignment name   : get_next_line
Expected files    : get_next_line.c get_next_line.h
Allowed functions : read, free, malloc
--------------------------------------------------------------------------------

Write a function named get_next_line which prototype should be:
char    *get_next_line(int fd);

Your function must return a line that has been read from the file descriptor
passed as parameter.

What we call a "line that has been read" is a succession of 0 to n characters
that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

The line should be returned including the '\n' in case there is one at the end
of the line that has been read.

When you've reached the EOF, you must store the current buffer in a char * and
return it. If the buffer is empty you must return NULL.

In case of error return NULL.

In case of not returning NULL, the pointer should be free-able.

Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be
used as the buffer size for the read calls in your functions.

Your function must be memory leak free.

When you've reached the EOF, your function should keep 0 memory allocated with
malloc except the line that has been returned.

Calling your function get_next_line in a loop will therefore allow you to read
the text available on a file descriptor one line at a time until the end of the
text, no matter the size of either the text or one of its lines.

Make sure that your function behaves well when it reads from a file, from the
standard output, from a redirection etc.

No call to another function will be done on the file descriptor between 2 calls
of get_next_line.

Finally we consider that get_next_line has an undefined behavior when reading
from a binary file.

You should use the test.sh to help you test your get_next_line.
*/

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif

// Helper: find character in string
static char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == 0)
		return (s);
	return (NULL);
}

// Helper: get string length
static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// Helper: duplicate string
static char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

// Helper: join two strings
static char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		join[len1 + i] = s2[i];
		i++;
	}
	join[len1 + len2] = '\0';
	return (join);
}

// Extract line from stash (up to and including \n, or until end if no \n)
static char	*extract_line(char *stash, char *newline)
{
	char	*line;
	size_t	line_len;
	size_t	i;

	if (!stash || !stash[0])
		return (NULL);
	if (newline)
		line_len = newline - stash + 1;
	else
		line_len = ft_strlen(stash);
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = stash[i];
		i++;
	}
	line[line_len] = '\0';
	return (line);
}

// Update stash with leftover data (what's after \n)
static char	*update_leftover(char *stash, char *newline)
{
	char	*leftover;

	if (!newline)
	{
		free(stash);
		return (NULL);
	}
	leftover = ft_strdup(newline + 1);
	free(stash);
	return (leftover);
}

// Main function
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*temp;
	char		*newline;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// Read until we have a newline or EOF
	while (!stash || !ft_strchr(stash, '\n'))
	{
		// Allocate buffer for reading
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
		{
			free(stash);
			return (NULL);
		}
		// Read from file descriptor
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// Handle read error
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		// Handle EOF (no more data)
		if (bytes_read == 0)
		{
			free(buffer);
			break ;
		}
		// Null-terminate the buffer
		buffer[bytes_read] = '\0';
		// Append buffer to stash
		if (!stash)
			stash = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(stash, buffer);
			free(stash);
			stash = temp;
		}
		free(buffer);
	}
	// Extract line
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	newline = ft_strchr(stash, '\n');
	line = extract_line(stash, newline);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	// Update stash with leftover
	stash = update_leftover(stash, newline);
	return (line);
}
