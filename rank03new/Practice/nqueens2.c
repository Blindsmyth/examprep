


static int  n;
static int  *board;

static void print_sol(void)
{
    int i = 0;

    while(i < n)
    {
        fprintf(stdout, %d, board[i]);
        if(i + 1 < n)
            fprintff(stdout," ");
        i++;
    }
    	fprintf(stdout, "\n");
}

int ok(int row, int col)
{
    int i = 0;

    while(i < col)
    {
        if( board[i] == row
            board[i] - row == col - i
            row - board[i] == col - i
            )
        return 0;
    i++;
    }
    return 1;
}

static void solve(int col)
{   
    int row = 0;

    if(col == n)
        {
            print_sol();
            return;
        }

    while(row < n)
    {
        if(ok(col, row))
            {
            board[col] = row;
            solve(col +1);
            }
        row++;
    }
}

int main (int argc, char **argv)
{
    if(argc != 2)
        return 0;
    n = atoi(argv[1]);
    if (n <= 0)
        return 1;
    int b[n];
    board = b;
    solve(0);
    return 1;
}