/*

Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"

00000010

mask
10000000


*/
#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int mask = 128;
	int i = 8;
	
	while (i > 0)
	{
		if (octet & mask)
			write (1, "1", 1);
		else
			write (1, "0", 1);
		mask = mask >> 1;
		i--;
	}	
}

int	main (void)
{
	print_bits(2);
	return 1;
}













