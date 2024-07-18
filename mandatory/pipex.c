#include "../pipex.h"

char **fill_cmnd_list(char ***arg_list, char **envp, int size)
{
    int i;
    char *path;
    char **cmnd_list;

    i = 0;
    path = NULL;
    cmnd_list = malloc(sizeof(char *) * (size + 1));
    cmnd_list[size] = 0;
    while (arg_list[i])
    {
        path = find_path(envp, arg_list[i][0]);
        if (!path)
            return (free_list(cmnd_list), free_list_list(arg_list), NULL);
        *(cmnd_list + i) = path;
        i++;
    }
    return (cmnd_list);
}

char ***fill_arg_list(char **cmnds, int size, char **envp)
{
    int check;
    char ***arg_list;
    char *path;
    int i;

    check = 0;
    i = -1;
    arg_list = malloc(sizeof(char **) * (size + 1));
    if (!arg_list)
        return (NULL);
    arg_list[size] = 0;
    while (++i < size)
    {
        arg_list[i] = flags(cmnds[i]);
        if (!arg_list[i])
            check = 1;
        path = find_path(envp, arg_list[i][0]);
        if (!path)
            check = 1;
        else
            free(path);
    }
    if (check == 1)
        return (free_list_list(arg_list), NULL);
    return (arg_list);
}

void continue_pipex(char *file_1, char *file_2, char *content, char ***arg_list, char **cmnd_list)
{
    int i;

    i = -1;
    if (!content && ft_strcmp(file_1, "/dev/stdin"))
    {
        content = special_case_dev(*cmnd_list, *arg_list);
        i++;
    }
    else if (!content)
        content = file_read(file_1);
    while (*(cmnd_list + ++i))
    {
        if (!content)
            break;
        content = exec_cmnd(*(cmnd_list + i), *(arg_list + i), content);
    }
    if (ft_strcmp(file_1, "here_doc"))
        i = open(file_2, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else    
        i = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (i == -1)
        return (perror("open"), free_them_all(content, cmnd_list, arg_list));
    if (content)
        write(i, content, strlen(content));
    return (close(i), free_them_all(content, cmnd_list, arg_list));
}

void pipex(char *file_1, char *file_2, char **cmnds, char **envp)
{
    int i;
    char *content;
    char **cmnd_list;
    char ***arg_list;

    content = NULL;
    i = 0;
    if (ft_strcmp(file_1, "here_doc"))
        content = get_next_line(0, cmnds++[0], -2);
    while (cmnds[i] != file_2)
        i++;
    arg_list = fill_arg_list(cmnds, i, envp);
    if (!arg_list)
        return ;
    cmnd_list = fill_cmnd_list(arg_list, envp, i);
    if (!cmnd_list)
    {
        if (content)
            free(content);
        free_list_list(arg_list);
        return ;
    }
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