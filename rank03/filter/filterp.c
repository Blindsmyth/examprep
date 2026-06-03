
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif





int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	char	*temp = NULL;
	char	*result = NULL;
	int	total_read = 0;
	ssize_t	bytes_current;
	
	if	(argc != 2 || argv[1][0] == '\0')
		return 1;
		
	while ((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, total_read + bytes_current + 1);
			if (!temp)
			{
				perror("Error");
				free(result);
				return 1;
			}
		result = temp;
		memmove(result + total_read, buffer, bytes_current);
		total_read += bytes_current;
	}
}







