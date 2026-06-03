/*Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf with the following constraints:

- It will manage only the following conversions: s,d, and x

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Your function must not leak.


Exemples of the function output:

call: ft_printf("Hello %s\n", "toto");
out:Hello toto$

call: ft_printf("Magic %s is %d", "number", 42);
out:Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out:Hexadecimal for 42 is 2a$

Warning: Your function must not have any leaks, this will be checked during moulinette
*/

#include <unistd.h>
#include <stdarg.h>

// Helper: calculate string length
int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

// Helper: write single character, return 1
int ft_putchar(char c)
{
	return (write(1, &c, 1));
}

// Helper: write string, return length
int ft_putstr(char *s)
{
	int i = 0;
	
	if (!s)
		s = "(null)";
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

// Helper: write integer recursively, return char count
int ft_putnbr(int n)
{
	int count = 0;
	unsigned int nbr;
	int digit;
	
	if (n < 0)
	{
		ft_putchar('-');
		count++;
		n += 1;
		n = -n;
		nbr = (unsigned int)n + 1;
	}
	else
		nbr = (unsigned int)n;
	
	if (nbr >= 10)
	{
		count += ft_putnbr((int)(nbr / 10));
	}
	digit = (nbr % 10) + '0';
	ft_putchar(digit);
	count++;
	return (count);
}

// Helper: write hex recursively, return char count
int ft_puthex(unsigned int n)
{
	int count = 0;
	char *hex = "0123456789abcdef";
	int digit;
	
	if (n >= 16)
	{
		count += ft_puthex(n / 16);
	}
	digit = hex[n % 16];
	ft_putchar(digit);
	count++;
	return (count);
}

// Main printf function
int ft_printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	int i = 0;
	
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (format[i] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (format[i] == 'x')
				count += ft_puthex(va_arg(args, unsigned int));
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

