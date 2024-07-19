#include "../../pipex.h"

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!(s))
	{
		s = "(null)";
		ft_putstr(s);
		return (6);
	}
	while (*(char *)(s + i))
	{
		write(1, s + i, 1);
		i++;
	}
	return (i);
}
