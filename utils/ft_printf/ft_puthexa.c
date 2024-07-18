/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:43:18 by cjuarez           #+#    #+#             */
/*   Updated: 2024/04/22 11:44:28 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	rec_func(unsigned int n, const char *base)
{
	if (n > 15)
	{
		rec_func(n / 16, base);
		rec_func(n % 16, base);
	}
	else
		write(1, base + n, 1);
}

int	ft_puthexa(unsigned int n, const char c)
{
	int			i;
	const char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	rec_func(n, base);
	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}
