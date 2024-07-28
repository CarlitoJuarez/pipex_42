/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:19:29 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 16:15:23 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

int	check_dir(int fd)
{
	int		bytes;
	char	*res;

	res = malloc(sizeof(char) * BUF_SIZE + 1);
	if (!res)
		return (0);
	bytes = read(fd, res, BUF_SIZE);
	if (bytes < 0 && errno == EISDIR)
		return (free_it(&res), close(fd), 4);
	return (free_it(&res), close(fd), 0);
}

char	*file_read(char *file)
{
	int		fd;
	char	*content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == 2)
			ft_printf("zsh: no such file or directory: %s\n", file);
		return (fill_cont(errno));
	}
	if (check_dir(fd) == 4)
		return (content = fill_dir(), content);
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
		return (0);
	}
	close(fd);
	return (1);
}
