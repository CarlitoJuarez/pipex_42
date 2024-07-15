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
            flags[k] = malloc(sizeof(char) * j + 1);
            flags[k][j] = 0;
            j = 0;
            while ( *(s + i + j) && !is_space(*(s + i + j)) )
            {
                flags[k][j] = *(s + i + j);
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
    flags = malloc(sizeof(char *) * args + 1);
    flags[args] = 0;
    i = 0;
    while ( *(s + i) && is_space(*(s + i)))
        i++;
    return (flags_continue(s, flags, args, i));
}

char *find_path(char **envp, char *cmnd)
{
    int i;
    char *path;
    char *full_path;
    char **arr;

    i = 0;
    path = NULL;
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
    i = 0;
    while (arr[i])
    {
        full_path = concat(arr[i], cmnd);
        if (!access(full_path, X_OK))
            return (full_path);
        i++;
    }
    printf("zsh: command not found: %s\n", cmnd);
    return (NULL);
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
        {
            free_list(cmnd_list);
            free_list_list(arg_list);
        }
        content = exec_cmnd(*(cmnd_list + i), *(arg_list + i), content);
        i++;
    }
    printf("CONTENT_FINAL: %s\n", content);
    fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_2 == -1)
        perror("open");
    if (content)
        write(fd_2, content, strlen(content));
}

void pipex(char *file_1, char *file_2, char **cmnds, char **envp)
{
    int i;
    int check;
    char *content;
    char **cmnd_list;
    char ***arg_list;

    content = NULL;
    i = 0;
    check = 0;
    while (cmnds[i] != file_2)
        i++;
    if (ft_strcmp(file_1, "here_doc"))
        content = get_next_line(0, cmnds++[0]);
    cmnd_list = malloc(sizeof(char *) * (i + 1));
    if (!cmnd_list)
        return ;
    arg_list = malloc(sizeof(char **) * (i + 1));
    if (!arg_list)
        return (free(cmnd_list));
    cmnd_list[i] = NULL;
    arg_list[i] = NULL;
    i = 0;
    while (cmnds[i] != file_2)
    {
        arg_list[i] = flags(cmnds[i]);
        if (!find_path(envp, arg_list[i][0]))
            check = 1;
        else
            cmnd_list[i] = find_path(envp, arg_list[i][0]);
        i++;
    }
    if (check == 1)
        return ;
    continue_pipex(file_1, file_2, content, arg_list, cmnd_list);
}



int main(int argc, char **argv, char **envp)
{
    if (argc == 5)
    {
        if ( !( file_check_w(argv[argc - 1]) && file_check_r(argv[1]) ) )
            return (0);
        pipex(argv[1], argv[argc - 1], argv + 2, envp);
    }
    else
        write(1, "\n", 1);
}