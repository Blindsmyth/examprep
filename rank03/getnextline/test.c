#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char	*get_next_line(int fd);

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc < 2)
		return (1);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Could not open file\n", 20);
		return (1);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, strlen(line));
		free(line);
	}

	close(fd);
	return (0);
}
