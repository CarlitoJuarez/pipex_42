/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:20:45 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:23:37 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_it(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

long	ft_atoi(char *s)
{
	size_t	i;
	size_t	res;

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

int	no_num_or_plus(char c)
{
	if ((c >= '0' && c <= '9') || c == '+')
		return (0);
	return (1);
}

int	check_num(char *s)
{
	long	i;

	i = 0;
	while (*(s + i))
	{
		if (no_num_or_plus(*(s + i)))
			return (0);
		i++;
	}
	i = ft_atoi(s);
	if (i > (long)INT_MAX)
		return (0);
	return (1);
}

int	is_head(char ***arg_list)
{
	int i;

	i = 0;
	while (arg_list[i])
	{
		if (ft_strcmp(arg_list[i][0], "head"))
			return (1);
		i++;
	}
	return (0);
}

int	cat_times(char ***arg_list)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arg_list[i])
	{
		if (ft_strcmp(arg_list[i][0], "cat"))
			j++;
		i++;
	}
	return (j);
}

char	*special_case_dev(char **cmnd_list, char ***arg_list, int i)
{
	if (!cmnd_list || !arg_list)
		return (NULL);
	if (i)
		return (NULL);
	if (ft_strcmp("ls", arg_list[0][0]))
		return (exec_cmnd_dev(*cmnd_list, *arg_list));
	else if (ft_strstr(arg_list[0][0], "head"))
	{
		if (arg_list[0][1] && ft_strcmp("-n", arg_list[0][1]))
		{
			if (check_num(arg_list[0][2]))
				return (get_next_line(0, "\n", ft_atoi(arg_list[0][2])));
			else
				ft_printf("head: illegal line count -- %s\n", arg_list[0][2]);
		}
		else if (!arg_list[0][1])
			return (get_next_line(0, "\n", 10));
	}
	else if (ft_strcmp(arg_list[0][0], "cat") && is_head(arg_list))
		return (get_next_line(0, "\n", 10 + cat_times(arg_list)));
	else if (ft_strcmp(arg_list[0][0], "cat") || ft_strcmp(arg_list[0][0], "wc")
			|| ft_strcmp(arg_list[0][0], "tail"))
		return (get_next_line(0, 0, -3));
	return (exec_cmnd_dev(*cmnd_list, *arg_list));
}
