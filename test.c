#include <stdlib.h>
#include <stdio.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    int i = 2;
    while (i * i <= n) 
    {
        if (n % i == 0)
            return 0;
        i++;
    }
    return 1;
}

int ft_atoi(char *str)
{
    int res = 0;
    int i = 0;
    
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    printf("%d\n", is_prime(ft_atoi(argv[1])));
    return 0;
}