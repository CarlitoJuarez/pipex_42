#ifndef SO_LONG_FH
# define SO_LONG_FH

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stddef.h>
# include <stdarg.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# define TILE_SIZE 50
# define WIN_HEIGHT 250
# define WIN_WIDTH 350

# define WALL "./assets/wall.xpm"
# define EMPTY "./assets/empty.xpm"
# define ME "./assets/me.xpm"
# define EXIT "./assets/exit.xpm"
# define MYSTERY "./assets/mystery.xpm"


typedef struct s_img
{
    void    *img_ptr;
    int    *img_pixels_ptr;

    int     bits_pp;
    int     endian;
    int     line_len;
}   t_img;

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *textures[5];

    char    **map;
    int     mystery;
    int     moves;

    t_img   img;
}   t_data;

// Make Move

void    move_up(t_data *data);
void    move_down(t_data *data);
void    move_left(t_data *data);
void    move_right(t_data *data);

// Utils 1

char    **create_map(char **map, t_data *data);

int     ft_putnbr(int num);

// CHECK MAP



// MAIN

int     on_destroy(t_data *data);
void    render_map(t_data *data);

#endif