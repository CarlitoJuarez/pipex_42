#include "../pipex.h"

size_t ft_strlen(char *s)
{
    size_t i;

    i = 0;
    while (*(s + i))
        i++;
    return (i);
}

char *fill_nil()
{
    char *s;

    s = malloc(sizeof(char) * (3 + 1));
    if (!s)
        return (NULL);
    s[0] = 'n';
    s[1] = 'i';
    s[2] = 'l';
    s[3] = '\0';
    return (s);
}