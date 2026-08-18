#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
    # define BUFFER_SIZE 5
# endif

static void filter(char *s, int slen, char *pattern, int patternlen)
{
    char    *pos;
    int i;
    char    *s_end = s + slen;

    pos = s;
    while((pos = memmem(pos, (size_t)(s_end - pos), pattern, (size_t)patternlen)))
    (
        i = 0;
        while(i < patternlen)
        {
            pos[i] = '*';
            i++;
        }
        pos += patternlen;
    )
    write(1, s, (size_t)slen);
}

int main(int argc, char **argv)
{
    if(argc < 3 || argv[1] == 0)
        return 1;
    
    char    b[BUFFER_SIZE + 1];
    char    *tmp = NULL; 
    char    *result = NULL;
    int total_read = 0;
    ssize_t bytes_current;

    while((bytes_current = read(0, b, BUFFER_SIZE)) > 0)
    {
        tmp = realloc(result, total_read + bytes_current + 1);
            if(!tmp)
            {
                perror("Error");
                free(result);
                return 1;
            }
        result = tmp;
        memmove(result, b, bytes_current);
        total_read += bytes_current;
    }
    if(bytes_current == -1)
    {
        perror("Error");
        free(result);
        return 1;
    }
    if(result)
    {
        result[bytes_total] = 0;
        filter(result, total_read, argv[1], (int)strlen(argv[1]));
    }
    return 0;
}