#include <unistd.h>
#include <stdio.h>

void	putword(char *string, int fd)
{
	int	i;
	
	i = 0;
	
	while(string[i] == ' ')
	{
	i++;
	}
	
	while(string[i] && string[i] != ' ')
		{
		write(fd, &string[i],1);
		i++;
		}
	return;
}

int main(int argc, char **argv)
{
	if (argc < 1)
		return (0);
		
	putword(argv[1],1);
	return (0);
}

