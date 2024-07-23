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

// int make_smaller(int size)
// {
//     if (size > 20000000)
//         size /= (1024 * 100);
//     else if (size > 2000000)
//         size /= (1024 * 100);
//     else if (size > 200000)
//         size /= (1024 * 10);
//     else if (size > 20000)
//         size /= 1024;
//     else if (size > 2000)
//         size /= 100.24;
//     else if (size > 200)
//         size /= 10.24;
//     else if (size > 20)
//         size = 20;
//     return (size);
// }