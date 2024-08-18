/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:47 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:31:48 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	rec_func_un(unsigned long n, const char *b)
{
	if (n > 9)
		rec_func_un(n / 10, b);
	ft_putchar(*(b + (n % 10)));
}

int	ft_putunsigned(unsigned long n)
{
	int			i;
	const char	*b;

	b = "0123456789";
	rec_func_un(n, b);
	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
