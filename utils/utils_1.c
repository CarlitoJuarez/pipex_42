#include "../pipex.h"



char *concat(char *path, char *cmnd)
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
    i = 0;
    while (*(path + i))
    {
        new[i] = path[i];
        i++;
    }
    new[i++] = '/';
    j = 0;
    while (*(cmnd + j))
    {
        new[i + j] = cmnd[j];
        j++;
    }
    return (new);
}

char *first(char *s)
{
    int i;
    int size;
    char *first;

    i = 0;
    size = 0;
    first = NULL;
    while (*(s + i))
    {
        if ( ( i == 0 && !is_space(*(s + i)) ) || ( is_space(*(s + i - 1) && !is_space(*(s + i))) ) )
        {
            while ( *(s + i + size) && !is_space(*(s + i + size)) )
                size++;
            first = malloc(sizeof(char) * size);
            first[size] = 0;
            size = 0;
            while ( *(s + i + size) &&  !is_space(*(s + i + size)) )
            {
                first[size] = *(s + i + size);
                size++;
            }
            break;
        }
        i++;
    }
    return (first);
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