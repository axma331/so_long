#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

# define COLOR 0x000FFCC00
# define EXIT "xpm/exit.xpm"
# define WALL "xpm/tree_1.1.xpm"
# define PLAYER1 "xpm/player_1.xpm"
# define PLAYER2 "xpm/player_2.xpm"
# define PLAYER3 "xpm/player_3.xpm"
# define PLAYER4 "xpm/player_4.xpm"
# define PLAYER5 "xpm/player_5.xpm"
# define PLAYER6 "xpm/player_6.xpm"

# define ITEM1 "xpm/item_1.xpm"
# define ITEM2 "xpm/item_2.xpm"
# define ITEM3 "xpm/item_3.xpm"
# define ITEM4 "xpm/item_4.xpm"

# define SKELETON1 "xpm/skeleton_1.xpm"
# define SKELETON2 "xpm/skeleton_2.xpm"
# define SKELETON3 "xpm/skeleton_3.xpm"
# define SKELETON4 "xpm/skeleton_4.xpm"

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
	int cnt;
	t_xpm	*background;
	t_xpm	*frontround;
	t_xpm	*exit;
	t_xpm	*item;
	t_xpm	*player1;
	t_xpm	*wall;
	t_xpm	*tmp;
	t_tmp	*temp;
	t_xpm	*player2;
	t_xpm	*player3;
	t_xpm	*player4;
	t_xpm	*player5;
	t_xpm	*player6;
	t_xpm	*skeleton1;
	t_xpm	*skeleton2;
	t_xpm	*skeleton3;
	t_xpm	*skeleton4;
	t_xpm	*imgground;
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
int 	player_movements(t_struct *s);
void background_for_img(t_struct *s, t_xpm *dest, int color);
int skeleton_movements(t_struct *s);

#endif