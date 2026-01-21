/*

Assignment name  : print_hex
Expected files   : print_hex.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a positive (or zero) number expressed in base 10,
and displays it in base 16 (lowercase letters) followed by a newline.

If the number of parameters is not 1, the program displays a newline.

Examples:

$> ./print_hex "10" | cat -e
a$
$> ./print_hex "255" | cat -e
ff$
$> ./print_hex "5156454" | cat -e
4eae66$
$> ./print_hex | cat -e
$

255
%10 = 5
/10 = 25


*/

#include <unistd.h>
#include <stdio.h>

#define BASE "0123456789abcdefg"

void	puthex (int	nbr)
{

	char c;
	if (nbr > 0)
	{
		puthex(nbr / 16);
		c = BASE[nbr % 16];
		write (1, &c, 1);
	}
}



int	is_space(char	c)
{
	return(c == ' ' || (c >= 9 && c <=13));
}


int	ft_atoi(char *str)
{
	int	sign = 1;
	int	res = 0;
	int	i = 0;
	int	len;
		
	
	while (is_space(str[i]))
	{
		i++;
	}
	
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	
	while(str[i] >= '0' && str[i] <= '9')
		{
		res = res * 10 + (str[i] - '0');
		i++;
		}
	return res;
}




int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write (1, "\n", 1);
		return 1;
	}
	puthex(ft_atoi(argv[1]));
	//ft_atoi("123456789");
}

