#include "../pipex.h"

int is_del(char c)
{
    if (c == ':')
        return (1);
    return (0);
}

int size_of(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (*(str + i))
    {
        if ( ( i == 0 && !is_del(*(str + i)) ) ||
        ( !is_del(*(str + i)) && is_del(*(str + (i - 1)))) )
            count++;
        i++;
    }
    return (count);
}

char **split_path_continue(char **arr, char *s, int size)
{
    int i;
    int j;
    int k;
    char *new;

    i = 0;
    j = 0;
    while (size)
    {
        k = 0;
        while (is_del(s[j]))
            j++;
        while (s[j + k] && !is_del(s[j + k]))
            k++;
        new = fill_str(k, s, j);
        if (!new)
            return (free_list(arr), NULL);
        arr[i++] = new;
        j += k;
        size--;
    }
    return (arr);
}

char **split_path(char *path)
{
    char **arr;
    int i;

    i = size_of(path);
    arr = malloc(sizeof(char *) * (i + 1));
    if (!arr)
        return (NULL);
    arr[i] = NULL;
    arr = split_path_continue(arr, path, i);
    return (arr);
}