/* Assignment name  : fprime
Expected files   : fprime.c
Allowed functions: printf, atoi
--------------------------------------------------------------------------------

Write a program that takes a positive int and displays its prime factors on the
standard output, followed by a newline.

Factors must be displayed in ascending order and separated by '*', so that
the expression in the output gives the right result.

If the number of parameters is not 1, simply display a newline.

The input, when there is one, will be valid.

Examples:

$> ./fprime 225225 | cat -e
3*3*5*5*7*11*13$
$> ./fprime 8333325 | cat -e
3*3*5*5*7*11*13*37$
$> ./fprime 9539 | cat -e
9539$
$> ./fprime 804577 | cat -e
804577$
$> ./fprime 42 | cat -e
2*3*7$
$> ./fprime 1 | cat -e
1$
$> ./fprime | cat -e
$
$> ./fprime 42 21 | cat -e
$
*/

#include "stdio.h"
#include "stdlib.h"

int	main(int argc, char **argv)
{
	int	i;
	int	num;

	i = 2;
	if (argc == 2)
	{
		num = atoi(argv[1]);
		if (num == 1)
			printf("1");
		while (i <= num)
		{
			if (num % i == 0)
			{
				printf("%d", i);
				if (num != i) // if num is not the last number. if it equals to i it means it is the last number
					printf("*");
				num = num / i;
			}
			else
				i++;
		}
	}
	printf("\n");
	return (0);
}

/*
42 % 2 = 0

print 2

num = 42
42 != 2

print *

num = 42 / 2
num = 21
i = 3

3 <= 21

21 % 3 = 0

print 3 
21 != 3

num = 21 / 3
num = 7

i = 4

4 <= 7

7 % 4 = 3

i = 5

7 % 5 = 2

i = 6

7 % 7 = 0
*/


/*


int num
int i = 2;


num = atoi(argv[1]);

while (i <= num)
{
	if (num % i == 0)
	{
		printf(%d,i);
		if (num != i)
			printf("*");
		num = num / i;
	}	
	else
		i++;
}

printf("\n");
return 0;
*/