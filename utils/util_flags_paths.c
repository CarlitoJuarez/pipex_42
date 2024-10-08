/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_flags_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:11:08 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 16:12:28 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**flags_continue(char *s, char **flags, int args, int i)
{
	int	j;
	int	k;

	k = 0;
	while (args)
	{
		if (*(s + i) && ((i == 0 && !is_space(*(s + i)))
				|| (is_space(*(s + i - 1)) && !is_space(*(s + i)))))
		{
			j = 0;
			while (*(s + i + j) && !is_space(*(s + i + j)))
				j++;
			flags[k] = fill_str(j, s, i);
			if (!flags[k])
				return (free_list(flags), flags = NULL, NULL);
			k++;
			args--;
			i += j;
		}
		else if (*(s + i) && is_space(*(s + i)))
			i++;
	}
	return (flags);
}

char	**flags(char *s)
{
	int		i;
	int		args;
	char	**flags;

	i = 0;
	args = 0;
	while (*(s + i))
	{
		if ((i == 0 && !is_space(*(s + i)))
			|| (is_space(*(s + i - 1)) && !is_space(*(s + i))))
			args++;
		i++;
	}
	if (!args)
		return (NULL);
	flags = malloc(sizeof(char *) * (args + 1));
	if (!flags)
		return (NULL);
	flags[args] = 0;
	i = 0;
	while (*(s + i) && is_space(*(s + i)))
		i++;
	return (flags_continue(s, flags, args, i));
}

int	trim_cmnd(char *cmnd)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (cmnd[++i])
	{
		if (cmnd[i] == '/')
			check = 1;
	}
	if (check == 1)
	{
		i--;
		while (cmnd[i] != '/')
			i--;
		return (++i);
	}
	return (0);
}

char	*find_path_2(char **arr, char *cmnd, char *content, char *last)
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
			full_path = find_path_2(arr, cmnd + trim_cmnd(cmnd), content, last);
		if (!access(full_path, X_OK) && check == 1)
			return (print_p(content, cmnd, 1, last), free_list(arr), full_path);
		else if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
	}
	return (print_p(content, cmnd, 0, last), free_list(arr), NULL);
}

char	*find_path(char **envp, char *cmnd, char *content, char *last)
{
	int		i;
	char	*path;
	char	**arr;

	i = 0;
	path = NULL;
	if (!cmnd)
		return (NULL);
	if (!access(cmnd, X_OK))
		return (print_p(content, cmnd, 1, last), fill_this(cmnd));
	while (i < 100 && envp[i])
	{
		if (ft_strcmp("PATH=", envp[i]))
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path || !*path || !envp[i] || i == 100)
		return (print_p(content, cmnd, 0, last), NULL);
	arr = split_path(path);
	if (!arr)
		return (NULL);
	return (find_path_2(arr, cmnd, content, last));
}
