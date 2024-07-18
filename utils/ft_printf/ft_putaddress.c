/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:14:54 by cjuarez           #+#    #+#             */
/*   Updated: 2024/04/22 11:52:22 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

void	func_rec(unsigned long n, const char *base)
{
	if (n > 15)
	{
		func_rec(n / 16, base);
		func_rec(n % 16, base);
	}
	else
		write(1, (base + n), 1);
}

int	ft_putaddress(void *p)
{
	const char		*base;
	unsigned long	n;
	int				i;

	i = 0;
	base = "0123456789abcdef";
	if (!p)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putstr("0x");
	n = (unsigned long)p;
	func_rec(n, base);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i + 2);
}
