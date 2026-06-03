#include <stdio.h>
#include <limits.h>
int ft_printf(const char *format, ...);
int main(void) {
    int ret1 = ft_printf("INT_MIN: %d\n", INT_MIN);
    int ret2 = printf("INT_MIN: %d\n", INT_MIN);
    printf("ft_printf returned: %d, printf returned: %d\n", ret1, ret2);
    return 0;
}
