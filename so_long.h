#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>

# define SPEED 5
# define COLOR 0x00099CC66

# define EXIT "xpm/exit.xpm"
# define WALL "xpm/tree.xpm"
# define COLLECTIBLE "xpm/collectible.xpm"

# define PLAYER1 "xpm/player_1.xpm"
# define PLAYER2 "xpm/player_2.xpm"
# define PLAYER3 "xpm/player_3.xpm"
# define PLAYER4 "xpm/player_4.xpm"
# define PLAYER5 "xpm/player_5.xpm"
# define PLAYER6 "xpm/player_6.xpm"

# define ENEMY1 "xpm/skeleton_1.xpm"
# define ENEMY2 "xpm/skeleton_2.xpm"
# define ENEMY3 "xpm/skeleton_3.xpm"
# define ENEMY4 "xpm/skeleton_4.xpm"

# define UP		13
# define LEFT	0
# define RIGHT	2
# define DOWN	1


typedef struct	s_info
{
	int	tmp;
	int	x;
	int	y;
	int	p_flag;
	int	e_flag;
	int	vertical;
	int	horizontal;
	int	player_y;
	int	player_x;
	int	enemy_x;
	int	enemy_y;
	int	steps_cnt;
	int	collectible_cnt;
	int	only_one_plyaer;
}				t_info;

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
	char **map;
	void *mlx_ptr;
	void *win_ptr;
	int cnt;
	int x;
	int y;
	t_info	info;
	t_xpm	*wall;
	t_xpm	*exit;
	t_xpm	*enemy[4];
	t_xpm	*player[6];
	t_xpm	*player_run[8];
	t_xpm	*collectible;
	t_xpm	*gameground;
}				t_struct;

void	*init_map(char *filmane);
void	init_idle_images(t_struct *s);
void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width, int height);
void	*init_mlx_new_window(t_struct *s);
void	creat_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color);
void	create_gameground(t_struct *s);
void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color);
void	moving_player(t_struct *s);
void	counting_panel(t_struct *s, t_xpm *dest, int color);
void	player_movements(t_struct *s);
void	enemy_movements(t_struct *s);

// void	init_mowement_images(t_struct *s);
// int player_run(t_struct *s);

int	image_pixel_get(t_xpm *data, int x, int y);
int	key_hook(int keycode, t_struct *s);
int	put_game(t_struct *s);

#endif
