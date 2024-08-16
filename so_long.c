#include "so_long.h"

int on_destroy(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

void render_map(t_data *data)
{
    int i;
    int j;
    char **map;

    i = 0;
    map = (*data).map;
    while (i < WIN_HEIGHT / TILE_SIZE)
    {
        j = 0;
        while (j < WIN_WIDTH / TILE_SIZE)
        {
            if (map[i][j] == 'P')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[0], j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == ' ')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[1], j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[2], j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'M')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[3], j * TILE_SIZE, i * TILE_SIZE);
            else if (map[i][j] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[4], j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;    
    }
}

int on_key_press(int keysym, t_data *data)
{
    if (keysym == XK_w)
        move_up(data);
    else if (keysym == XK_a)
        move_left(data);
    else if (keysym == XK_s)
        move_down(data);
    else if (keysym == XK_d)
        move_right(data);
    write(1, "MOVES: ", 7);
    return (ft_putnbr((*data).moves), write(1, "\n", 1), 1);
}

void    map_map(t_data *data)
{
    int tile_size;

    tile_size = TILE_SIZE;

    data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, ME, &tile_size, &tile_size);
    data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, EMPTY, &tile_size, &tile_size);
    data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &tile_size, &tile_size);
    data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, MYSTERY, &tile_size, &tile_size);
    data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, EXIT, &tile_size, &tile_size);
}

int main(void)
{
    t_data data;
    char *init_map[] = {
        "1111111",
        "1P 1E 1",
        "1 M1 M1",
        "1 M  11",
        "1111111",
        NULL
    };
    char **map;
    data.mystery = 0;
    data.moves = 0;
    printf("PENIS: %d\n", data.mystery);
    map = create_map(init_map, &data);
    check_map(data);
    data.map = map;
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "so_long");
    if (!data.win_ptr)
        return (free(data.mlx_ptr), 1);
    // load the tiles into the data struct
    map_map(&data);
    // creating a new image
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    if (!data.img.img_ptr)
        return (1);
    // Filling the img struct with data
    data.img.img_pixels_ptr = (int *)mlx_get_data_addr(data.img.img_ptr, &data.img.bits_pp, &data.img.line_len, &data.img.endian);
    // render_pixels(data);
    render_map(&data);
    // mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img_ptr, 0, 0);
    mlx_key_hook(data.win_ptr, &on_key_press, &data);
    mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
    mlx_loop(data.mlx_ptr);
    return (0);
}