/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:20:45 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/28 16:17:11 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_err(int errnum)
{
	if (!(errnum == 13))
		perror("open:");
}

long	ft_atoi(char *s)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	if (*s == '+')
		i++;
	while (*(s + i))
	{
		res = res * 10 + (*(s + i) - '0');
		i++;
	}
	return (res);
}

int	no_num_or_plus(char c)
{
	if ((c >= '0' && c <= '9') || c == '+')
		return (0);
	return (1);
}

int	check_num(char *s)
{
	long	i;

	i = 0;
	while (*(s + i))
	{
		if (no_num_or_plus(*(s + i)))
			return (0);
		i++;
	}
	i = ft_atoi(s);
	if (i > (long)INT_MAX)
		return (0);
	return (1);
}

void	print_p(char *c, char *cmnd, int access, char *last)
{
	if (ft_strcmp("dir", c) && access)
		ft_printf("%s: error reading 'standard input': Is a directory\n", cmnd);
	if (!ft_strcmp(cmnd, last))
	{
		if (!ft_strcmp("exi", c) && !access && !ft_strcmp("nil", cmnd)
			&& trim_cmnd(cmnd) && !ft_strcmp("acc", last))
			ft_printf("zsh: no such file or directory: %s\n", cmnd);
		else if (!ft_strcmp("exi", c) && !ft_strcmp("per", c)
			&& !ft_strcmp("nil", cmnd) && !access && !trim_cmnd(cmnd))
			ft_printf("zsh: command not found: %s\n", cmnd);
		else if (ft_strcmp("per", c))
			ft_printf("zsh: permission denied: inpermission\n");
	}
	else if (!trim_cmnd(cmnd) && !access && !ft_strcmp("acc", last))
		ft_printf("zsh: command not found: %s\n", cmnd);
	else if (!access && !ft_strcmp("acc", last))
		ft_printf("zsh: no such file or directory: %s\n", cmnd);
	else if (ft_strcmp("acc", cmnd))
		ft_printf("zsh: permission denied: outfile\n");
}
