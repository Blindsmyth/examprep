#include <unistd.h>


int	ft_putchar(char c)
{
	write(1, &c, 1);
	return 1;
}

int	ft_putstr(char *s)
{
	int i = 0;
	
	if (!s)
	{
		s = "(null)";
	}

	while(s[i])
	{
	write(1, &s[i], 1);
	}
	return i;
}

int 	ft_putnbr(int n)
{
	int count = 0;
	
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

int	main ()
{
	
	ft_putnbr(123456789);
	return (0);
}
