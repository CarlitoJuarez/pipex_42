#include "../pipex.h"

char *special_case_dev(char *cmnd_list, char **arg_list)
{

    if (ft_strcmp("ls", arg_list[0]))
        return (exec_cmnd_dev(cmnd_list, arg_list));
    else if (ft_strcmp("head", arg_list[0]) && ft_strcmp("-n", arg_list[1]))
        return (get_next_line(0, "\n", atoi(arg_list[2])));
    return (NULL);
}