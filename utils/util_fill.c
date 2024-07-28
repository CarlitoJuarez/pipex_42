/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:22:13 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 17:19:41 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

char	*fill_acc(char *this)
{
	char	*s;

	if (this)
		free(this);
	this = NULL;
	s = malloc(sizeof(char) * (3 + 1));
	if (!s)
		return (NULL);
	s[0] = 'a';
	s[1] = 'c';
	s[2] = 'c';
	s[3] = '\0';
	return (s);
}

char	*fill_dir(void)
{
	char	*s;

	s = malloc(sizeof(char) * (3 + 1));
	if (!s)
		return (NULL);
	s[0] = 'd';
	s[1] = 'i';
	s[2] = 'r';
	s[3] = 0;
	return (s);
}

char	*fill_cont(int errnum)
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

char	*fill_this(char *this)
{
	int		i;
	char	*s;

	i = 0;
	if (!this || !*this)
		return (NULL);
	while (*(this + i))
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (!s)
		return (NULL);
	s[i] = 0;
	i = 0;
	while (*(this + i))
	{
		*(s + i) = *(this + i);
		i++;
	}
	return (s);
}
