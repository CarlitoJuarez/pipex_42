/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:06:43 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:07:26 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**fill_cmnd_list(char ***arg_list, char **envp, int size)
{
	int		i;
	char	*path;
	char	**cmnd_list;

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

char	***fill_arg_list(char **cmnds, int size, char **envp)
{
	int		check;
	char	***arg_list;
	char	*path;
	int		i;

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

void	continue_pipex(char **argv, char *content,
			char ***arg_list, char **cmnd_list)
{
	int	i;

	i = -1;
	if (!content && ft_strcmp(argv[1], "/dev/stdin"))
		content = special_case_dev(*cmnd_list, arg_list[++i]);
	if (!content)
		content = file_read(argv[1]);
	while (*(cmnd_list + ++i))
	{
		printf("cont: %s\n", content);
		if (!content)
			break ;
		content = exec_cmnd(*(cmnd_list + i), *(arg_list + i), content);
	}
	if (ft_strcmp(argv[1], "here_doc"))
		i = open(argv[i + 3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		i = open(argv[i + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i == -1)
		return (perror("open"), free_them_all(content, cmnd_list, arg_list));
	if (content)
		write(i, content, strlen(content));
	return (close(i), free_them_all(content, cmnd_list, arg_list));
}

void	pipex(char **argv, char **envp)
{
	int		i;
	char	*content;
	char	**cmnd_list;
	char	***arg_list;

	content = NULL;
	i = 0;
	if (ft_strcmp(argv[1], "here_doc"))
		content = get_next_line(0, argv++[2], -2);
	while (argv[3 + i])
		i++;
	arg_list = fill_arg_list(argv + 2, i, envp);
	if (!arg_list && content)
		return (free(content));
	else if (!arg_list && !content)
		return ;
	cmnd_list = fill_cmnd_list(arg_list, envp, i);
	if (!cmnd_list && content)
		return (free_list_list(arg_list), free(content));
	else if (!cmnd_list && !content)
		return (free_list_list(arg_list));
	continue_pipex(argv, content, arg_list, cmnd_list);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		if (!(file_check_w(argv[argc - 1]) && file_check_r(argv[1])))
			return (0);
		pipex(argv, envp);
	}
	return (0);
}
