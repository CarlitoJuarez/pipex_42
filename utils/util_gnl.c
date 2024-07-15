#include "../pipex.h"

int check_end(char *res, char *limiter)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (*(limiter + j))
        j++;
    while (*(res + i) && *(res + i) != '\n')
        i++;
    i -= j;
    if (i < 0)
        return (0);
    j = 0;
    while ( *(res + i + j) == *(limiter + j) )
        j++;
    if (*(res + i + j) == '\n' || !*(res + i + j))
        return (1);
    return (0);
}

char *read_this(int fd, char *buf, char *limiter)
{
    char *res;
    int bytes;

    res = malloc(sizeof(char) * BUF_SIZE + 1);
    if (!res)
        return(NULL);
    bytes = 1;
    while (bytes > 0)
    {
		if (fd == 0)
        	write(1, ">> ", 3);
        bytes = read(fd, res, BUF_SIZE);
        if (!bytes)
            break;
        else if (bytes < 0)
        {
            perror("read");
            if (res)
                free(res);
            return (NULL);
        }
        res[bytes] = 0;
        if (fd == 0 && check_end(res, limiter))
            break;
        buf = ft_strjoin(buf, res);
    }
    free(res);
    return (buf);
}


char *get_next_line(int fd, char *limiter)
{
    static char *buf;

    if (buf)
        free(buf);
    buf = NULL;
    buf = read_this(fd, buf, limiter);
    if (!buf)
        return (NULL);
    return (buf);
}