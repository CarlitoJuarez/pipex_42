/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:19:29 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:20:25 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*file_read(char *file)
{
	int		fd;
	char	*content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == 2)
			ft_printf("zsh: no such file or directory: %s\n", file);
		else if (errno == 14)
			ft_printf("zsh: permission denied: %s\n", file);
		return (NULL);
	}
	if (check_dir(fd) == 4)
		return ("readdir");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (ft_strcmp(file, "/dev/urandom"))
		content = get_next_line(fd, "\n", 40);
	else
		content = get_next_line(fd, 0, -1);
	close(fd);
	if (!content)
		return (NULL);
	return (content);
}

int	file_check_r(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == 2)
			return (1);
		return (0);
	}
	close(fd);
	return (1);
}

int	file_check_w(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY);
	if (fd == -1)
	{
		if (errno == 2)
			return (1);
		if (errno == 13)
			ft_printf("zsh: permission denied: %s\n", file);
		return (0);
	}
	close(fd);
	return (1);
}

void	free_list(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		i++;
	i--;
	while (i)
		free_it((arr + i--));
	free(*arr);
	free(arr);
}

void	free_list_list(char ***arr)
{
	int	i;

	i = 0;
	while (*(arr + i))
		i++;
	i--;
	while (i)
		free_list(*(arr + i--));
	free_list(*arr);
	free(arr);
}
