

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif








int	main (int argc, char **argv)
{
	char	temp[BUFFER_SIZE];
	char	*buffer;
	char	*res = NULL;
	int	total_read = 0;
	ssize_t bytes_current;
	
	if (argc != 2)
		return 1;
	
	while((bytes_current = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(res, (total_read + bytes_current + 1));
		if (!buffer)
		{
			perror("realloc");
			free(res);
			return 1;
		}
		res = buffer;
		
		memmove((res + total_read), temp, bytes_current);
		total_read = total_read + bytes_current;
		res[total_read] = '\0';
	}
	
	if (bytes_current < 0)
	{
		free(res);
		perror("read");
		return 1;
	}
	
	if (!res)
		return 1;
	
	// TODO: Add filtering logic here
	// ft_filter(res, argv[1]);
	
	free(res);
	return 0;
}
