#include "../pipex.h"

char **flags_continue(char *s, char **flags, int args, int i)
{
    int j;
    int k;

    k = 0;
    while (args)
    {
        if ( *(s + i) && (( i == 0 && !is_space(*(s + i)) ) || ( is_space(*(s + i - 1)) && !is_space(*(s + i)))) )
        {
            j = 0;
            while ( *(s + i + j) && !is_space(*(s + i + j)))
                j++;
            flags[k] = fill_str(j, s, i);
            if (!flags[k])
                return (free_list(flags), flags = NULL, NULL);
            k++;
            args--;
            i += j;
        }
        else if ( *(s + i) && is_space(*(s + i)) )
            i++;
    }
    return (flags);
}

char **flags(char *s)
{
    int i;
    int args;
    char **flags;

    i = 0;
    args = 0;
    while (*(s + i))
    {
        if ( ( i == 0 && !is_space(*(s + i)) ) || ( is_space(*(s + i - 1)) && !is_space(*(s + i))) )
            args++;
        i++;
    }
    if (!args)
        return (NULL);
    flags = malloc(sizeof(char *) * (args + 1));
    if(!flags)
        return (NULL);
    flags[args] = 0;
    i = 0;
    while ( *(s + i) && is_space(*(s + i)))
        i++;
    return (flags_continue(s, flags, args, i));
}

char *find_path_continue(char **arr, char *cmnd)
{
    int i;
    char *full_path;

    i = 0;
    while (arr[i])
    {
        full_path = concat_full_path(arr[i++], cmnd);
        if (!full_path)
            return (free_list(arr), NULL);
        if (!access(full_path, X_OK))
            return (free_list(arr), full_path);
        free(full_path);
    }
    return (ft_printf("zsh: command not found: %s\n", cmnd), free_list(arr), NULL);
}

char *find_path(char **envp, char *cmnd)
{
    int i;
    char *path;
    char **arr;

    i = 0;
    path = NULL;
    if (!cmnd)
        return (NULL);
    while (i < 100 && envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path = envp[i] + 5;
            break;
        }
        i++;
    }
    if (!path || !*path || !envp[i] || i == 100)
        return (printf("zsh: command not found: %s\n", cmnd), NULL);
    arr = split_path(path);
    if (!arr)
        return (NULL);
    return (find_path_continue(arr, cmnd));
}