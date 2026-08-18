#include <stdio.h>

int min_removals(char *s)
{
    int i;
    int balance;
    int remove;

    i = 0;
    balance = 0;
    remove = 0;
    while (s[i])
    {
        if (s[i] == '(')
            balance++;
        else if (balance > 0)
            balance--;
        else
            remove++;
        i++;
    }
    return (remove + balance);
}

void solve(char *s, int i, int balance, int removed, int min)
{
    char c;

    if (balance < 0 || removed > min)
        return;
    if (s[i] == '\0')
    {
        if (balance == 0 && removed == min)
            puts(s);
        return;
    }
    c = s[i];

    if (c == '(')
        solve(s, i + 1, balance + 1, removed, min);
    else if (balance > 0)
        solve(s, i + 1, balance - 1, removed, min);

    s[i] = ' ';
    solve(s, i + 1, balance, removed + 1, min);
    s[i] = c;
}

int main(int argc, char **argv)
{
    int min;

    if (argc != 2)
        return (1);
    min = min_removals(argv[1]);
    solve(argv[1], 0, 0, 0, min);
    return (0);
}