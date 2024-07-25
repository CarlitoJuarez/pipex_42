/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:07:14 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/23 15:09:42 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**fill_cmnd_list(char ***arg_list, char **envp, int size, char *content)
{
	int		i;
	int		check;
	char	*path;
	char	**cmnd_list;

	i = -1;
	check = 0;
	cmnd_list = malloc(sizeof(char *) * (size + 1));
	if (!cmnd_list)
		return (NULL);
	cmnd_list[size] = 0;
	while (arg_list && arg_list[++i])
	{	
		path = find_path(envp, arg_list[i][0], content);
		if (!path || (path && ft_strcmp("exi", content)))
			*(cmnd_list + i) = fill_nil(path);
		else
			*(cmnd_list + i) = path;
		if (path && ft_strcmp(content, "dir") && i == 0 && !any_of_those(arg_list[0][0]))
			check = 1;
		content = NULL;
	}
	if (check == 1)
		ft_printf("%s: error reading 'standard input': Is a directory\n", (arg_list[0][0]));
	return (cmnd_list);
}

char	***fill_arg_list(char **cmnds, int size)
{
	char	***arg_list;
	int		i;

	i = -1;
	arg_list = malloc(sizeof(char **) * (size + 1));
	if (!arg_list)
		return (NULL);
	arg_list[size] = 0;
	while (++i < size)
		arg_list[i] = flags(cmnds[i]);
	return (arg_list);
}

void	continue_pipex(char **argv, char *c,
				char ***arg_list, char **ls)
{
	int	i;

	i = -1;

	if (!c && ft_strcmp(argv[1], "/dev/stdin"))
		c = special_case_dev(ls, arg_list, ++i);
	while (ls && *(ls + ++i))
	{
		if (ft_strcmp(*(ls + i), "nil") || any_of_those(c))
			free_it(&c);
		else
			c = exec_cmnd(*(ls + i), *(arg_list + i), c);	
	}
	if (ft_strcmp(argv[0], "here_doc"))
		i = open(argv[i + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		i = open(argv[i + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i == -1)
		return (perror("open"), free_a(c, ls, arg_list));
	if (!c)
		return (write(i, "", 0), close(i), free_a(c, ls, arg_list));
	else
		return (write(i, c, ft_strlen(c)), close(i), free_a(c, ls, arg_list));
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
		argv++;
	while (argv[3 + i])
		i++;
	if (ft_strcmp(argv[0], "here_doc"))
		content = get_next_line(0, argv[1], -2);
	else if (!content && !ft_strcmp(argv[1], "/dev/stdin"))
		content = file_read(argv[1]);
	arg_list = fill_arg_list(argv + 2, i);
	cmnd_list = fill_cmnd_list(arg_list, envp, i, content);
	continue_pipex(argv, content, arg_list, cmnd_list);
}

int	main(int argc, char **argv, char **envp)
{
	if (BUF_SIZE > (long)INT_MAX)
		return (ft_printf("BUF_SIZE to large. %dl\n", BUF_SIZE), 0);
	else if (BUF_SIZE <= 0)
		return (ft_printf("BUF_SIZE must be positive. %dl\n", BUF_SIZE), 0);
	if (argc >= 5)
	{
		if (!(file_check_w(argv[argc - 1])))
			return (0);
		pipex(argv, envp);
	}
	return (0);
}
