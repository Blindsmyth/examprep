#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define N   4

void    biNarutoHelper(int idx, int digits, char *s)
{
    // Base Case
    if(idx == digits)
        printf("%s\n", s);

    // Recursion
    else
    {
        s[idx] = '0';
        biNarutoHelper(idx + 1, digits, s);

        s[idx] = '1';
        biNarutoHelper(idx + 1, digits, s);
    }
}


void    biNaruto(int digits)
{
    char    *s;

    s = calloc(digits + 1, sizeof(*s));
    if (!s)
    {
        perror("Calloc failed");
        return;
    }
    biNarutoHelper(0, digits, s);
    free(s);
}


int main()
{
    biNaruto(N);
}