/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_special.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:19:37 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 16:21:16 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	is_head(char ***arg_list)
{
	int	i;

	i = 0;
	while (arg_list[i])
	{
		if (ft_strstr(arg_list[i][0], "head"))
		{
			if (!arg_list[i][2])
				return (10);
			else if (ft_strcmp(arg_list[i][1], "-n"))
				return (ft_atoi(arg_list[i][2]));
		}
		i++;
	}
	return (0);
}

char	*valid_cat_2(char **arr, char *cmnd)
{
	int		i;
	int		check;
	char	*full_path;

	i = 0;
	check = 0;
	while (arr[i])
	{
		if (!trim_cmnd(cmnd))
		{
			full_path = concat_full_path(arr[i++], cmnd + trim_cmnd(cmnd));
			check = 1;
		}
		else if (access(cmnd, X_OK))
			break ;
		else
			full_path = valid_cat_2(arr, cmnd + trim_cmnd(cmnd));
		if (!access(full_path, X_OK) && check == 1)
			return (free_list(arr), full_path);
		else if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
	}
	return (free_list(arr), NULL);
}

int	valid_cat(char **envp, char *cmnd)
{
	int		i;
	char	*path;
	char	**arr;

	i = 0;
	path = NULL;
	while (i < 100 && envp[i])
	{
		if (ft_strcmp("PATH=", envp[i]))
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	arr = split_path(path);
	if (!arr)
		return (0);
	path = valid_cat_2(arr, cmnd);
	if (path)
		return (free(path), 1);
	return (0);
}

int	cat_times(char ***arg_list, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg_list[i])
	{
		printf("J: %d\n", j);
		if (ft_strcmp(arg_list[i][0] + trim_cmnd(arg_list[i][0]), "cat")
		&& valid_cat(envp, arg_list[i][0]))
			j++;
		else
			return (j);
		i++;
	}
	j += is_head(arg_list);
	return (j);
}

char	*special_dev(char **cmnd_list, char ***arg_list, int i, char **envp)
{
	if (!cmnd_list || !arg_list)
		return (NULL);
	if (i)
		return (NULL);
	if (ft_strcmp("ls", arg_list[0][0]))
		return (exec_cmnd_dev(*cmnd_list, *arg_list));
	else if (ft_strcmp(arg_list[0][0], "head"))
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
	else if (ft_strstr(arg_list[0][0], "cat") && is_head(arg_list))
		return (get_next_line(0, "\n", cat_times(arg_list, envp)));
	else if (ft_strstr(arg_list[0][0], "cat") || ft_strstr(arg_list[0][0], "wc")
			|| ft_strstr(arg_list[0][0], "tail"))
		return (get_next_line(0, 0, -3));
	return (exec_cmnd_dev(*cmnd_list, *arg_list));
}
