#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <unistd.h>

# define UP		13
# define LEFT	0
# define RIGHT	2
# define DOWN	1
# define ESC	53

# define SPEED 5
# define COLOR 0x00099CC66

typedef struct s_temp
{
	char	**mas;
	char	*steps;
	char	*collect;
	int		t1;
	int		t2;
	int		x;
	int		y;
	int		ret;
}			t_temp;

typedef struct s_info
{
	int		x;
	int		y;
	int		v;
	int		h;
	int		p_flag;
	int		e_flag;
	int		c_flag;
	int		esc_flag;
	int		s_cnt;
	int		c_cnt;
	int		only_one_plyaer;
}			t_info;

typedef struct s_xpm
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}			t_xpm;

typedef struct s_struct
{
	char	**map;
	void	*mlx_ptr;
	void	*win_ptr;
	int		cnt;
	int		x;
	int		y;
	t_temp	t;
	t_info	info;
	t_xpm	*wall;
	t_xpm	*exit;
	t_xpm	*enemy[4];
	t_xpm	*player[6];
	t_xpm	*player_a[4];
	t_xpm	*collectible;
	t_xpm	*gameground;
}			t_struct;

void	init_map(char *filmane, t_struct *s);
void	init_idle_images(t_struct *s);
void	*init_mlx_img(t_struct *s, char *xpm_file, int width, int height);
void	*init_mlx_new_window(t_struct *s);
void	draw_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color);
void	create_gameground(t_struct *s, int x, int y);
void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color);
void	moving_player(t_struct *s);
void	draw_panel(t_struct *s, t_xpm *dest, int color);
void	draw_player(t_struct *s);
void	draw_player_movements(t_struct *s);
void	draw_enemy(t_struct *s);
void	checking_map(t_struct *s);
void	checking_map_first_line(t_struct *s);
void	pars_mapname(t_temp t, int argc, char **argv);
int		pixel_get(t_xpm *data, int x, int y);
int		key_hook(int keycode, t_struct *s);
int		create_game(t_struct *s);
int		ft_close(int keycode, t_struct *s);
void	ft_exit_so_long(t_struct *s, char *msg, int errno);

/*v - vertical*/
/*h - horizontal*/
/*s_cnt - steps counter*/
/*c_cnt - collectible counter*/
/*bpp - bits_per_pixel*/
/*ll - line_length*/
/*w - *width*/
/*h - heigth*/

#endif
