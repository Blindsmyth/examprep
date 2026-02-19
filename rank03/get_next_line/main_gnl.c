/*
 * Minimal main to test get_next_line. Reads from stdin (fd 0).
 * Run: ./test_gnl < test.txt   or   echo -e "line1\nline2" | ./test_gnl
 *
 * Compile: cc -D BUFFER_SIZE=42 get_next_line.c main_gnl.c -o test_gnl
 */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(0);
	}
	return (0);
}
