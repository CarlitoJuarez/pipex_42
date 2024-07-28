/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:17:27 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 16:22:00 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_it(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
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

void	free_a(char *content, char **cmnd_list, char ***arg_list)
{
	if (content)
		free_it(&content);
	if (cmnd_list)
		free_list(cmnd_list);
	if (arg_list)
		free_list_list(arg_list);
}
