#include "../so_long.h"

int real_check (char **map)
{
    int i;
    int j;
    int *coord;

    coord[0] = 0;
    coord[1] = 0;
    find_elem(&coord, map, 'P');
    
}

int check_count(char **map)
{
    int i;
    int j;
    int player_exit;

    i = 0;
    player_exit = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P' || map[i][j] == 'E')
                player_exit++;
            j++;
        }
        i++;
    }
    if (player_exit != 2)
        return (0);
}

int check_map(t_data data)
{
    if (!(data.mystery))
        return (0);
    if (!(check_count(data.map)))
        return (0);
    if (!real_check(data.map))
        return (0);
}