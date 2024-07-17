#include "../pipex.h"

char **flags_continue(char *s, char **flags, int args, int i)
{
    int j;
    int k;
    char **arr;

    arr = flags;
    k = 0;
    while (args)
    {
        if ( *(s + i) && (( i == 0 && !is_space(*(s + i)) ) || ( is_space(*(s + i - 1)) && !is_space(*(s + i)))) )
        {
            j = 0;
            while ( *(s + i + j) && !is_space(*(s + i + j)))
                j++;
            arr[k] = malloc(sizeof(char) * (j + 1));
            if (!arr[k])
                return (free_list(flags), NULL);
            arr[k][j] = 0;
            j = 0;
            while ( *(s + i + j) && !is_space(*(s + i + j)) )
            {
                arr[k][j] = *(s + i + j);
                j++;
            }
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
    char **res;

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
        return (res = NULL, NULL);
    flags[args] = 0;
    i = 0;
    while ( *(s + i) && is_space(*(s + i)))
        i++;
    res = flags_continue(s, flags, args, i);
    if (!res)
        return (flags = NULL, NULL);
    return (res);
}

// char *return_path(char **arr, int index)
// {
//     int i;
//     char *path;

//     i = 0;
//     while (*(arr[index] + i))
//         i++;
//     path = malloc(sizeof(char) * (i + 1));
//     if (!path)
//         return (NULL);
//     i = 0;
//     while (*(arr[index] + i))
//     {
//         path[i] = *(arr[index] + i);
//         i++;
//     }
//     free_list(arr);
//     return ();
// }

char *find_path(char **envp, char *cmnd)
{
    int i;
    char *path;
    char *full_path;
    char **arr;

    i = 0;
    path = NULL;
    full_path = NULL;
    if (!cmnd)
        return (NULL);
    while (i < 100)
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path = envp[i] + 5;
            break;
        }
        i++;
    }
    if (!path)
        return (write(1, "Error: No path found.\n", 22), NULL);
    arr = split_it(path);
    if (!arr)
        return (NULL);
    i = 0;
    while (arr[i])
    {
        full_path = concat(arr[i], cmnd);
        if (!full_path)
        {
            free_list(arr);
            arr = NULL;
            return (NULL);
        }
        if (!access(full_path, X_OK))
        {
            free_list(arr);
            arr = NULL;
            return (full_path);
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    return (printf("zsh: command not found: %s\n", cmnd), free_list(arr), NULL);
}

void continue_pipex(char *file_1, char *file_2, char *content, char ***arg_list, char **cmnd_list)
{
    int i;
    int fd_2;

    i = 0;
    if (!content)
        content = file_read(file_1);
    while (*(cmnd_list + i))
    {
        if (!content)
            break;
        printf("EXEC: %s\n", content);
        content = exec_cmnd(*(cmnd_list + i), *(arg_list + i), content);
        i++;
    }
    fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_2 == -1)
    {
        perror("open");
        if (content)
        {
            free(content);
            content = NULL;
        }
        free_list(cmnd_list);
        free_list_list(arg_list);
        return ;
    }
    if (content)
        write(fd_2, content, strlen(content));
    close(fd_2);
    free(content);
    content = NULL;
    free_list(cmnd_list);
    free_list_list(arg_list);
}

void pipex(char *file_1, char *file_2, char **cmnds, char **envp)
{
    int i;
    // int check;
    char *content;
    char **cmnd_list;
    char ***arg_list;

    content = NULL;
    i = 0;
    // check = 0;
    while (cmnds[i] != file_2)
        i++;
    if (ft_strcmp(file_1, "here_doc"))
    {
        content = get_next_line(0, cmnds++[0]);
        if (!content)
            return ;
    }
    cmnd_list = malloc(sizeof(char *) * (i + 1));
    if (!cmnd_list && content)
        return (free(content));
    else if (!cmnd_list && !content)
        return ;
    arg_list = malloc(sizeof(char **) * (i + 1));
    if (!arg_list && content)
        return (free(cmnd_list), free(content));
    else if (!arg_list && !content)
        return (free(cmnd_list));
    cmnd_list[i] = NULL;
    arg_list[i] = NULL;
    i = 0;
    while (cmnds[i] != file_2)
    {
        arg_list[i] = flags(cmnds[i]);
        if (!arg_list[i])
        {
            free_list_list(arg_list);
            free_list(cmnd_list);
            if (content)
                free(content);
            return;
        }
        cmnd_list[i] = find_path(envp, arg_list[i][0]);
        if (!cmnd_list[i])
        {
            free_list_list(arg_list);
            free_list(cmnd_list);
            if (content)
                free(content);
            return ;
        }
        // if (!find_path(envp, arg_list[i][0]))
        // {
        //     check = 1;
        //     // free_list_list(arg_list);
        //     // free_list(cmnd_list);
        //     // return ;
        // }
        // else
        //     cmnd_list[i] = find_path(envp, arg_list[i][0]);
        i++;
    }
    // if (check == 1)
    // {
    //     free_list_list(arg_list);
    //     free_list(cmnd_list);
    //     return ;
    // }
    continue_pipex(file_1, file_2, content, arg_list, cmnd_list);
}



int main(int argc, char **argv, char **envp)
{
    if (argc >= 5)
    {
        if ( !( file_check_w(argv[argc - 1]) && file_check_r(argv[1]) ) )
            return (0);
        pipex(argv[1], argv[argc - 1], argv + 2, envp);
    }
}