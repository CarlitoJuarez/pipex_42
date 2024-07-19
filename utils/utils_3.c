#include "../pipex.h"

long ft_atoi(char *s)
{
    size_t i;
    size_t res;

    i = 0;
    res = 0;
    if (*s == '+')
        i++;
    while (*(s + i))
    {
        res = res * 10 + (*(s + i) - '0');
        i++;
    }
    return (res);
}

int no_num_or_plus(char c)
{
    if( ( c >= '0' && c <= '9' ) || c == '+')
        return (0);
    return (1);
}

int check_num(char *s)
{
    long i;

    i = 0;
    while (*(s + i))
    {
        if ( no_num_or_plus(*(s + i)) )
            return (0);
        i++;
    }
    i = ft_atoi(s);
    if (i > (long)INT_MAX)
        return (0);
    return (1);
}

char *special_case_dev(char *cmnd_list, char **arg_list)
{
    if (ft_strcmp("ls", arg_list[0]))
        return (exec_cmnd_dev(cmnd_list, arg_list));
    else if (ft_strcmp("head", arg_list[0]) && arg_list[1] && ft_strcmp("-n", arg_list[1]) )
    {
        if (check_num(arg_list[2]))
            return (get_next_line(0, "\n", ft_atoi(arg_list[2])));
        else
            ft_printf("head: illegal line count -- %s\n", arg_list[2]);
    }
    return (NULL);
}