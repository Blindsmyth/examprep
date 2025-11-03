/*

Assignment name  : ft_swap
Expected files   : ft_swap.c
Allowed functions: 
--------------------------------------------------------------------------------

Write a function that swaps the contents of two integers the adresses of which
are passed as parameters.

Your function must be declared as follows:

void	ft_swap(int *a, int *b);

*/
#include <unistd.h>
#include <stdlib.h>

void	ft_swap(int *a, int *b)
{
	int	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	main ()
{
	int	*a;
	int	*b;
	
	a = malloc(sizeof(int));
	b = malloc(sizeof(int));
	
	*a = 1;
	*b = 2;
	
	ft_swap(a,b);
	return 1;
}
