#include <stdio.h>
#include <unistd.h>

int ft_printf(const char *format, ...);

int main(void)
{
	int ret;
	
	// Exam Example 1
	write(1, "Test 1: ", 8);
	ret = ft_printf("Hello %s\n", "toto");
	printf("[returned %d]\n\n", ret);
	
	// Exam Example 2
	write(1, "Test 2: ", 8);
	ret = ft_printf("Magic %s is %d", "number", 42);
	printf(" [returned %d]\n\n", ret);
	
	// Exam Example 3
	write(1, "Test 3: ", 8);
	ret = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("[returned %d]\n\n", ret);
	
	// Verify against real printf
	write(1, "\n--- Comparison ---\n", 20);
	int r1 = ft_printf("ft: %s %d %x\n", "test", 99, 255);
	int r2 = printf("og: %s %d %x\n", "test", 99, 255);
	printf("Both returned: %d and %d %s\n", 
		r1, r2, (r1 == r2) ? "✓" : "✗");
	
	return (0);
}




