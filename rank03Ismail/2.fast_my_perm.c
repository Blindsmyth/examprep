#include <unistd.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_swap(char *a, char *b)
{
    char tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_string(char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
                ft_swap(&str[i], &str[j]);
            j++;
        }
        i++;
    }
}

void permute(char *str, char *result, int *used, int pos, int len)
{
    int i;

    if (pos == len)
    {
        write(1, result, len);
        write(1, "\n", 1);
        return;
    }
    i = 0;
    while (i < len)
    {
        if (!used[i])
        {
            used[i] = 1;
            result[pos] = str[i];
            permute(str, result, used, pos + 1, len);
            used[i] = 0;
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    int len;
    int i;

    if (argc != 2)
        return (1);
    len = ft_strlen(argv[1]);
    char result[len + 1];
    int used[len];
    sort_string(argv[1]);
    i = 0;
    while (i < len)
    {
        used[i] = 0;
        i++;
    }
    result[len] = '\0';
    permute(argv[1], result, used, 0, len);
    return (0);
}