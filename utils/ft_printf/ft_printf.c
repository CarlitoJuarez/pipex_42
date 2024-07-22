/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjuarez <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:31:04 by cjuarez           #+#    #+#             */
/*   Updated: 2024/07/22 16:31:05 by cjuarez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../pipex.h"

static int	func1(va_list args, const char c)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putaddress(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), c));
	else if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned long)));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	int		j;
	int		i;
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	i = -1;
	j = 0;
	while (s && *(s + ++i))
	{
		if (*(s + i) == '%' && ft_strchr("cspdiuxX", *(s + i + 1)))
		{
			j += func1(args, *(s + i + 1));
			i++;
		}
		else
		{
			if ((*(s + i) == '%') && (*(s + i + 1) == '%'))
				i++;
			ft_putchar(*(s + i));
			j++;
		}
	}
	return (va_end(args), j);
}
