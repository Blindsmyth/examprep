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

*/

#include <unistd.h>
#include <stdio.h>

#define HEX "0123456789abcdef"


void	print_hex(int nbr)
{
	char c;
	
	// Base case: if nbr is 0, do nothing (let the caller handle it)
	if (nbr == 0) {
		return;
	}
	
	// Recursive case: process the number
	if (nbr > 0) {
		// First, recursively process the higher digits
		print_hex(nbr / 16);
		
		// Then print the current digit
		c = HEX[nbr % 16];
		write(1, &c, 1);
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;
	
	i = 0;
	sign = 1;
	res = 0;
	
	if (str[i] == '0')
	return (0);
	
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
		
	if (str[i] == '-')
	{
		sign = -1;	
		i++;
	}
		
	while (str[i] >= '0' && str[i] <= '9')
	{
	res = res * 10 + (str[i] - '0');
	i++;
	}
	

	printf("%d,\n", sign * res);
		return (sign * res);
}


int	main(int argc, char **argv)
{
	if (argc != 2)
	write(1, "\n", 1);
	
	print_hex(ft_atoi(argv[1]));
	return (1);
}

