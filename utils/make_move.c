#include "../so_long.h"

void find_elem(int **coord, char **map_2, char c)
{
    int i;
    int j;

    i = 0;
    while (map_2[i] && !(*coord)[0])
    {
        j = 0;
        while (map_2[i][j])
        {
            if (map_2[i][j] == c)
            {
                (*coord)[0] = i;
                (*coord)[1] = j;
                return ;
            }
            j++;
        }
        i++;
    }
}

void move_up(t_data *data)
{
    int *coord;

    coord = malloc(sizeof(int) * 2);
    coord[0] = 0;
    coord[1] = 0;
    find_elem(&coord, (data->map), 'P');
    if (data->map[coord[0] - 1][coord[1]] == '1')
        return ;
    else if (data->map[coord[0] - 1][coord[1]] == 'E' && data->mystery)
        return ;
    else if (data->map[coord[0] - 1][coord[1]] == 'E')
    {
        data->moves++;
        on_destroy(data);
    }
    else
    {
        if (data->map[coord[0] - 1][coord[1]] == 'M')
            data->mystery--;
        data->map[coord[0]][coord[1]] = ' ';
        data->map[coord[0] - 1][coord[1]] = 'P'; 
        data->moves++;
        render_map(data);
    }
}

void move_left(t_data *data)
{
    int *coord;

    coord = malloc(sizeof(int) * 2);
    coord[0] = 0;
    coord[1] = 0;
    find_elem(&coord, (data->map), 'P');
    if (data->map[coord[0]][coord[1] - 1] == '1')
        return ;
    else if (data->map[coord[0]][coord[1] - 1] == 'E' && data->mystery)
        return ;
    else if (data->map[coord[0]][coord[1] - 1] == 'E')
    {
        data->moves++;
        on_destroy(data);
    }
    else
    {
        if (data->map[coord[0]][coord[1] - 1] == 'M')
            data->mystery--;
        data->map[coord[0]][coord[1]] = ' ';
        data->map[coord[0]][coord[1] - 1] = 'P';
        data->moves++;
        render_map(data);
    }
}

void move_down(t_data *data)
{
    int *coord;

    coord = malloc(sizeof(int) * 2);
    coord[0] = 0;
    coord[1] = 0;
    find_elem(&coord, (data->map), 'P');
    if (data->map[coord[0] + 1][coord[1]] == '1')
        return ;
    else if (data->map[coord[0] + 1][coord[1]] == 'E' && data->mystery)
        return ;
    else if (data->map[coord[0] + 1][coord[1]] == 'E')
    {
        data->moves++;
        on_destroy(data);
    }
    else
    {
        if (data->map[coord[0] + 1][coord[1]] == 'M')
            data->mystery--;
        data->map[coord[0]][coord[1]] = ' ';
        data->map[coord[0] + 1][coord[1]] = 'P'; 
        data->moves++;
        render_map(data);
    }
}

void move_right(t_data *data)
{
    int *coord;

    coord = malloc(sizeof(int) * 2);
    coord[0] = 0;
    coord[1] = 0;
    find_elem(&coord, ((data)->map), 'P');
    if ((data)->map[coord[0]][coord[1] + 1] == '1')
        return ;
    else if ((data)->map[coord[0]][coord[1] + 1] == 'E' && (data)->mystery)
        return ;
    else if ((data)->map[coord[0]][coord[1] + 1] == 'E')
    {
        data->moves++;
        on_destroy(data);
    }
    else
    {
        if ((data)->map[coord[0]][coord[1] + 1] == 'M')
            (data)->mystery--;
        (*data).map[coord[0]][coord[1]] = ' ';
        (*data).map[coord[0]][coord[1] + 1] = 'P';
        data->moves++;
        render_map(data);
    }
    printf("hi\n");
}
