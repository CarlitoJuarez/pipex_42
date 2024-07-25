/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:26:34 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/23 15:07:28 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	get_size(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && *(s1 + i))
		i++;
	j = 0;
	while (*(s2 + j))
		j++;
	return (i + j);
}

char	*ft_strjoin(char *s1, char *s2, int times)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = get_size(s1, s2);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = 0;
	i = 0;
	while (s1 && *(s1 + i))
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (*(s2 + j))
		new[i++] = s2[j++];
	free(s1);
	if (times != 0)
		free(s2);
	return (new);
}

int	ft_strstr(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] == s1[i + j])
		{
			if (s2[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*read_this(int fd, char *buf, char *lim, int t)
{
	char	*res;
	int		bytes;

	bytes = 1;
	while (bytes > 0 && t != 0)
	{
		res = malloc(sizeof(char) * 1024 + 1);
		if (!res)
			return (NULL);
		if (fd == 0 && t == -2)
			write(1, "pipe heredoc> ", 15);
		bytes = read(fd, res, 10);
		if (bytes < 0)
			return (perror("read"), free(res), NULL);
		res[bytes] = 0;
		if ((fd == 0 && t == -2 && (res[0] != '\n'
					&& ft_strcmp(res, lim))) || !bytes)
			break ;
		if ((fd == 0 || ft_strcmp("\n", lim)) && t > 0 && ft_strstr(res, lim))
			t--;
		buf = ft_strjoin(buf, res, t);
	}
	if (res)
		free(res);
	return (buf);
}

char	*get_next_line(int fd, char *limiter, int times)
{
	static char	*buf;
	char *res;
	int bytes;

	buf = NULL;
	if (times == -3)
	{
		bytes = 1;
		while (bytes)
		{
			res = malloc(sizeof(char) * BUF_SIZE + 1);
			if (!res) 
				return (NULL);
			bytes = read(fd, res, BUF_SIZE);
			if (bytes < 0)
				return (perror("read"), free(res), NULL);
			free(res);
		}
	}
	buf = read_this(fd, buf, limiter, times);
	if (!buf)
		return (NULL);
	return (buf);
}
