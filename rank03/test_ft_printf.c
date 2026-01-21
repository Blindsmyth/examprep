#include <stdio.h>

int ft_printf(const char *format, ...);

int main(void)
{
	int ret1, ret2, ret3;
	
	// Test 1: from exam
	printf("Test 1:\n");
	ret1 = ft_printf("Hello %s\n", "toto");
	printf("Return: %d\n\n", ret1);
	
	// Test 2: from exam (no newline in original)
	printf("Test 2:\n");
	ret2 = ft_printf("Magic %s is %d", "number", 42);
	printf("\nReturn: %d\n\n", ret2);
	
	// Test 3: from exam
	printf("Test 3:\n");
	ret3 = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("Return: %d\n\n", ret3);
	
	// Additional edge case tests
	printf("=== Edge Cases ===\n");
	printf("Negative: ");
	ft_printf("%d\n", -42);
	
	printf("Zero: ");
	ft_printf("%d %x\n", 0, 0);
	
	printf("NULL: ");
	ft_printf("%s\n", NULL);
	
	printf("Hex 255: ");
	ft_printf("%x\n", 255);
	
	printf("INT_MIN: ");
	ft_printf("%d\n", -2147483648);
	
	printf("\nComparison with real printf:\n");
	printf("ft_printf: ");
	ret1 = ft_printf("Test %s %d %x\n", "hello", 42, 255);
	printf("Real printf: ");
	ret2 = printf("Test %s %d %x\n", "hello", 42, 255);
	printf("ft_printf returned: %d, printf returned: %d\n", ret1, ret2);
	
	return (0);
}

