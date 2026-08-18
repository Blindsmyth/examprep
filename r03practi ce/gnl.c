char *get_next_line(int fd)
{
    static char *stash = NULL;
    char    *buffer;
    char    *temp;
    char    *newline;
    char    *line;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    while (!stash || !ft_strchr(stash, '/n'))
        {
        buffer = malloc(sizeof(char) * BUFFER_SIZE +1)
        if (!buffer)
        {
            free(stash);
            return(NULL);
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);

        if(bytes_read < 0)
        {
            free(buffer);
            free(stash);
            return(NULL);

        if(bytes_read == 0)
        {
            free(buffer);
            break;
        }

        buffer[bytes_read] = '/0';

        if(!stash)
            stash = ft_strdup(buffer);
            free(stash);
            stash = temp;


        }
        free buffer
        }

        if(!stash || !stash[0])
        {
            free(stash);
            
        }
}