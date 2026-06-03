
#define GNU_SOURCE

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	filter(char *s, int slen, char *pattern, int patternlen)
{
	char	*pattern_start;
	char	*s_end;


}




int	main(int argc, char **argv)
{
	char	buffer[BUFFER_SIZE];
	char	*temp = NULL;
	char	*result = NULL;
	int	total_read = 0;
	ssize_t	bytes_current = 0;
	
	while ((bytes_current = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, total_read + bytes_current + 1);
			if(!temp)
			{
			perror("ERROR");
			free(result);
			return 1;
			}
		result = temp;
		memmove(result + total_read, buffer, bytes_current);
		total_read += bytes_current;
	}
	if (bytes_current == -1)
	{
		perror("Error");
		free(result);
		return 1;
	}
	if (result)
		{
		result[total_read] = 0;
		filter(result, total_read, argv[1], strlen(argv[1]));
		}
}


