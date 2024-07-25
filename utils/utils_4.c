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

char	*fill_nil(char *path)
{
	char	*s;

	if (path)
		free(path);
	path = NULL;
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
		return (free_it(&res), close(fd), 4);
	return (free_it(&res), close(fd), 0);
}

void print_permission(char *c, char *cmnd, int access)
{
	if (ft_strcmp(c, "perm"))
		ft_printf("zsh: permission denied: inpermission\n");
	else if (!ft_strcmp(c, "exi") && !access)
		ft_printf("zsh: command not found: %s\n", cmnd);

}

char *fill_dir(void)
{
	char *s;

	s = malloc(sizeof(char) * (3 + 1));
	if (!s)
		return (NULL);
	s[0] = 'd';
	s[1] = 'i';
	s[2] = 'r';
	s[3] = 0;
	return (s);
}

char *fill_cont(int errnum)
{
	char	*s;

	s = malloc(sizeof(char) * (3 + 1));
	if (!s)
		return (NULL);
	if (errnum == 13)
	{
		s[0] = 'p';
		s[1] = 'e';
		s[2] = 'r';
		s[3] = 0;
	}
	else if (errnum == 2)
	{
		s[0] = 'e';
		s[1] = 'x';
		s[2] = 'i';
		s[3] = 0;
	}
	else
		return (NULL);
	return (s);
}

int any_of_those(char *content)
{
	if (content && (ft_strcmp("per", content)
		|| ft_strcmp("exi", content) || ft_strcmp("ls", content)))
		return(1);
	return (0);
}