#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

# define TREE "trees/tree_1.1.xpm"


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
}				t_xpm;

typedef struct	s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
	int x_pos;
	int y_pos;
	t_data	*background;
	t_xpm	*wall;
	t_xpm	*tmp;
	t_data	*img;
	t_data *img_bord;
}				t_struct;

char	**init_map(char **str);
void	*init_mlx_new_or_xpm_file_to_image(t_struct *s, char *xpm_file, int width,int height);
void	*init_mlx_new_window(t_struct *s, char **map, char *xpm_file);
void	*create_background(t_struct *s, char **map, int b_lt, int b_up, int color);
void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color);
void	creat_floor(t_struct *s, int color);
int		image_pixel_get(t_xpm *data, int x, int y);

#endif