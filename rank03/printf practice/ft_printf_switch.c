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
#include <stdlib.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
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

int	ft_putnbr(int n)
{
	unsigned int	nbr;
	int		count = 0;
	int		digit;

	if (n < 0)
	{
		ft_putchar('-');
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

int	ft_puthex(unsigned int nbr)
{
	int	count = 0;
	char	*hex = "0123456789abcdef";
	int	digit;

	if (nbr >= 16)
	{
		count += ft_puthex(nbr / 16);
	}
	digit = hex[nbr % 16];
	ft_putchar(digit);
	count++;
	return (count);
}

int	ft_printf(const char *format, ...)	/* '...' is C syntax for a variadic function */
{
	va_list	ap;
	int	d;
	unsigned int	x;
	char	*s;
	int	count = 0;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			switch (*format++)
			{
			case 's':			/* string */
				s = va_arg(ap, char *);
				count += ft_putstr(s);
				break;
			case 'd':			/* int */
				d = va_arg(ap, int);
				count += ft_putnbr(d);
				break;
			case 'x':			/* hexadecimal */
				x = va_arg(ap, unsigned int);
				count += ft_puthex(x);
				break;
			default:
				/* If not a recognized conversion, print the % and character */
				count += ft_putchar('%');
				count += ft_putchar(*(format - 1));
				break;
			}
		}
		else
		{
			count += ft_putchar(*format++);
		}
	}
	va_end(ap);
	return (count);
}

int	main(void)
{
	ft_printf("Hello %s, %d, %x\n", "world", 42, 42);
	return (0);
}

