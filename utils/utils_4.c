/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:16:44 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/30 10:31:04 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	check_ls(char **arr, char *str)
{
	int	i;

	i = 0;
	while (*(arr + i))
	{
		if (ft_strstr(*(arr + i), str))
			return (1);
		i++;
	}
	return (0);
}

char	*pass_c(char *c)
{
	if (any_of_those(c) || ft_strcmp("dir", c))
		free_it(&c);
	return (c);
}

void	exit_fail(char *content, char **cmnd_list, int fd)
{
	perror("pipe");
	free_a(content, cmnd_list, NULL);
	close(fd);
	exit(EXIT_FAILURE);
}
