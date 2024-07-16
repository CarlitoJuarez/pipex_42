#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while ( s1 && *(s1 + i) )
		i++;
	j = 0;
	while (*(s2 + j))
		j++;
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (NULL);
	new[i + j] = 0;
	i = 0;
	while ( s1 && *(s1 + i) )
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (*(s2 + j))
		new[i++] = s2[j++];
    free(s2);
	return (new);
}

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

    bytes = 1;
    while (bytes > 0)
    {
        res = malloc(sizeof(char) * BUF_SIZE + 1);
        if (!res)
            return(NULL);
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