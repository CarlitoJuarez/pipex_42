#include "../pipex.h"

char *concat_full_path(char *path, char *cmnd)
{
    int i;
    int j;
    int size;
    char *new;

    i = 0;
    j = 0;
    while (*(cmnd + i))
        i++;
    while (*(path + j))
        j++;
    size = i + j;
    new = malloc(sizeof(char) * (size + 2));
    if (!new)
        return (NULL);
    new[size + 1] = 0;
    i = -1;
    while (*(path + ++i))
        new[i] = path[i];
    new[i++] = '/';
    j = -1;
    while (*(cmnd + ++j))
        new[i + j] = cmnd[j];
    return (new);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while ( *(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	if (*(s1 + i) == '\n' || !(*(s1 + i)))
		return (1);
	return (0);
}

int is_space(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

char *fill_str(int size, char *s, int index)
{
    char *res;
    int i;

    i = 0;
    res = malloc(sizeof(char) * (size + 1));
    if (!res)
        return (NULL);
    res[size] = 0;
    while (size)
    {
        res[i] = *(s + index + i);
        i++;
        size--;
    }
    return (res);
}