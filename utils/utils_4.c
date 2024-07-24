/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:02:41 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/23 15:08:07 by cjuarez          ###   ########.fr       */
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

char	*fill_nil(void)
{
	char	*s;

	s = malloc(sizeof(char) * (3 + 1));
	if (!s)
		return (NULL);
	s[0] = 'n';
	s[1] = 'i';
	s[2] = 'l';
	s[3] = '\0';
	return (s);
}

int check_dir(int fd)
{
	int bytes;
	char *res;

	res = malloc(sizeof(char) * BUF_SIZE + 1);
	if (!res) 
		return (0);
	bytes = read(fd, res, BUF_SIZE);
	if (bytes < 0 && errno == EISDIR)
		return (free_it(&res), 4);
	return (free_it(&res), 0);
}