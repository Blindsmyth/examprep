#include <stdio.h>
#include <stdlib.h>

static int n;
static int  *board;


int main (int argc, char **argv)
{
    if(argc != 2)
        return 1;
    n = atoi(argv[1]);
    if (n <= 0)
        return 0;
    int buf[n];
    board = buf;
    solve 0;
    return 0;
}