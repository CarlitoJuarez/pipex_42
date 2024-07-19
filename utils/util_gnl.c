#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2, int times)
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
	i = -1;
	while ( s1 && *(s1 + ++i) )
		new[i] = s1[i];
	j = 0;
	while (*(s2 + j))
		new[i++] = s2[j++];
    free(s1);
    if (times != 0)
        free(s2);
	return (new);
}

int ft_strstr(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] == s1[i + j])
		{
			if (s2[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char *read_this(int fd, char *buf, char *limiter, int times)
{
    char *res;
    int bytes;

    bytes = 1;
    while (bytes > 0 && times != 0)
    {
        res = malloc(sizeof(char) * BUF_SIZE + 1);
        if (!res)
            return(NULL);
		if (fd == 0 && times == -2)
        	write(1, "pipe heredoc> ", 14);
        bytes = read(fd, res, BUF_SIZE);
        if (bytes < 0)
            return (perror("read"), free(res), NULL);
        res[bytes] = 0;
        if ( ( fd == 0 && times == -2 && ft_strcmp(res, limiter) ) || !bytes )
            break;
        if (fd == 0 && times > 0 && ft_strstr(res, limiter))
            times--;
        buf = ft_strjoin(buf, res, times);
    }
    if (res)
        free(res);
    return (buf);
}

char *get_next_line(int fd, char *limiter, int times)
{
    static char *buf;

    buf = NULL;
    buf = read_this(fd, buf, limiter, times);
    if (!buf)
        return (NULL);
    return (buf);
}