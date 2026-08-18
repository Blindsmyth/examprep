static int len;
static char *str;

int is_balanced(char *str)
{
    int balance = 0;
    int i = 0;

    while(str[i])
    {
        if(str[i] == '(')
            balance++;
        if(str[i] == ')')
            balance--;
        if(balance < 0)
            return 0;
        i++;
    }
    return (balance == 0);


}

int min_removes(char *str)
{
    int i = 0;
    int open = 0;
    int closed = 0;

    while(str[i])
    {
        if(str[i] == '(')
            open++;
        if(str[i] == ')')
            if(open > 0)
                open--
            closed++;
        i++;
    }
    return (open + closed);
}

static void solve(int idx, int removes)
{
    int i;
    char    tmp;

    if(idx == len)
    {
        if(is_balanced(str))
            prints();
            return;
    }

    i = idx;
    while(i < len)
    {
        tmp =  str[i];
        str[i] = ' ';
        solve(i + 1, removes - 1)
        str[i] = tmp;
        i++;
    }


}

int main(int argc, char **argv)
{
    int removes;

    str = argv[1];
    removes = min_removes(str);
    if(removes == 0)
    {
        prints();
        return 0;
    }
    solve(0, removes);
    return 0;
}