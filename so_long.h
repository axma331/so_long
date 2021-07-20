#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

# define COLOR 0x0000FF00
# define WALL "xpm/tree_1.1.xpm"
# define PLAYER "xpm/player.xpm"
# define ITEM "xpm/item.xpm"
# define EXIT "xpm/exit.xpm"


typedef struct	s_data
{
	void *img_ptr;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}				t_data;

typedef struct	s_xpm
{
	void *ptr;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	int	width;
	int	heigth;
	int x_pos; /*удалить*/
	int y_pos; /*удалить*/
}				t_xpm;

typedef struct	s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
	int x_pos;
	int y_pos;
	t_xpm	*background;
	t_xpm	*frontround;
	t_xpm	*exit;
	t_xpm	*item;
	t_xpm	*player;
	t_xpm	*wall;
	t_xpm	*tmp;
	t_data	*img;
	// t_data *img_bord;
}				t_struct;

char	**init_map(char **str);
void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width,int height);
void	*init_mlx_new_window(t_struct *s, char **map);
void	create_background(t_struct *s, char **map);
void	create_frontround(t_struct *s, char **map);
void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color);
int		image_pixel_get(t_xpm *data, int x, int y);
void	creat_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color);
void	init_xpm_images(t_struct *s);
void	put_game(t_struct *s, char **map);

#endif