#include "../so_long.h"

int count_this(char **this, t_data *data)
{
    int i;
    int j;

    i = 0;
    while (this[i])
    {
        j = 0;
        while (this[i][j])
        {
            if (this[i][j] == 'M')
                data->mystery++;
            j++;
        }
        i++;
    }
    return (i);
}

char **create_map(char **init_map, t_data *data)
{
    int i;
    int j;
    int count;
    char **map;
    
    count = count_this(init_map, data);
    map = malloc(sizeof(char *) * (count + 1));
    map[count] = 0;
    i = 0;
    while (count)
    {
        j = 0;
        while (init_map[i][j])
            j++;
        map[i] = malloc(sizeof(char) * j + 1);
        if (!map[i])
            return (NULL);
        map[i][j] = 0;
        j = -1;
        while (init_map[i][++j])
            map[i][j] = init_map[i][j];
        i++;
        count--;
    }
    return (map);
}
void	rec_func_2(int n)
{
	char	c;

	if (n == INT_MIN)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		n = 147483648;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		rec_func_2(n / 10);
		rec_func_2(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	rec_func_2(n);
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}