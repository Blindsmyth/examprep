#include <unistd.h>


void	putnbr (int nbr)
{
	char	c;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		putnbr(nbr / 10);
	c = (nbr % 10) + '0';
	write(1, &c, 1);
}

void	putstr (char *s)
{
	int	i;
	
	i = 0;
	
	while (s[i])
	{
	write (1, &s[i], 1);
	i++;
	}
}

int main (void)
{
	int i;

	i = 1;

	while (i < 101)
	{
		if (i % 15 == 0)
		putstr ("fizzbuzz");
		else if (i % 3 == 0)
		putstr("fizz");
		else if (i % 5 == 0)
		putstr("buzz");
		else putnbr(i);
		i++;
	}
}
