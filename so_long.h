#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

# define COLOR 0x00000CC00
# define WALL "xpm/tree_1.1.xpm"
# define PLAYER "xpm/player.xpm"
# define ITEM "xpm/item.xpm"
# define EXIT "xpm/exit.xpm"

# define UP		13
# define LEFT	0
# define RIGHT	2
# define DOWN	1


typedef struct	s_tmp
{
	int ret;
	int fd;
	int t1;
	int t2;
}				t_tmp;

typedef struct	s_xpm
{
	void *ptr;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	int	width;
	int	heigth;
	double	x_pos;
	double	y_pos;
}				t_xpm;

typedef struct	s_struct
{
	char **map;
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
	int v;
	int g;
	int x_pos;
	int y_pos;
	int steps;
	int collec;
	t_xpm	*background;
	t_xpm	*frontround;
	t_xpm	*exit;
	t_xpm	*item;
	t_xpm	*player;
	t_xpm	*wall;
	t_xpm	*tmp;
	t_tmp	*temp;
	// t_data *img_bord;
}				t_struct;

char	**init_map(char **str);
void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width,int height);
void	*init_mlx_new_window(t_struct *s);
void	create_background(t_struct *s);
void	create_frontround(t_struct *s);
void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color);
int		image_pixel_get(t_xpm *data, int x, int y);
void	creat_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color);
void	init_xpm_images(t_struct *s);
void	*put_game(t_struct *s);
void	moving_player(t_struct *s);
int		key_hook(int keycode, t_struct *s);
void	background_for_steps(t_struct *s, t_xpm *dest, int color);

#endif