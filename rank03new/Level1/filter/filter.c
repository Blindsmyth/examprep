#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 4096

char	*read_all(size_t *out_size)
{
	size_t	capacity = BUF_SIZE;
	char	*buffer;
	char	*new_buffer;
	size_t	total = 0;
	ssize_t	nread;

	buffer = malloc(capacity + 1);
	if (!buffer)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return (NULL);
	}
	while ((nread = read(0, buffer + total, BUF_SIZE)) > 0)
	{
		total += nread;
		if (total + BUF_SIZE >= capacity)
		{
			capacity *= 2;
			new_buffer = realloc(buffer, capacity + 1);
			if (!new_buffer)
			{
				free(buffer);
				fprintf(stderr, "Error: realloc failed\n");
				return (NULL);
			}
			buffer = new_buffer;
		}
	}
	if (nread < 0)
	{
		free(buffer);
		fprintf(stderr, "Error: read error\n");
		return (NULL);
	}
	buffer[total] = '\0';
	if (out_size)
		*out_size = total;
	return (buffer);
}

void	ft_replace(char *hay, char *needle)
{
	size_t	i;
	size_t	needle_len;
	char	*pos;

	needle_len = strlen(needle);
	if (needle_len == 0)
		return ;
	pos = hay;
	while ((pos = memmem(pos, strlen(pos), needle, needle_len)) != NULL)
	{
		i = 0;
		while (i < needle_len)
		{
			pos[i] = '*';
			i++;
		}
		pos += needle_len;
	}
}

int	main(int argc, char **argv)
{
	size_t	input_size;
	char	*input;
	char	*needle;

	if (argc != 2 || argv[1][0] == '\0')   // fixed: catches empty argument
		return (1);
	needle = argv[1];
	input = read_all(&input_size);
	if (!input)
		return (1);
	if (strlen(needle) > 0)
		ft_replace(input, needle);
	write(1, input, input_size);
	free(input);
	return (0);
}
