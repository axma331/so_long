#include "so_long.h"

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
		s->i.v = -1;
	else if (keycode == DOWN)
		s->i.v = 1;
	if (keycode == LEFT)
		s->i.h = -1;
	if (keycode == RIGHT)
		s->i.h = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		ft_exit("The window is closed!", 0);
	}
	ft_bzero(&s->t, sizeof(t_temp));
	moving_player(s);
	return (0);
}

void	moving_player(t_struct *s)
{
	while (s->map[s->t.t1])
	{
		if (s->map[s->t.t1][s->t.t2] == 'P' && \
		(s->map[s->t.t1 + s->i.v][s->t.t2 + s->i.h] != '1' && \
							(s->i.v || s->i.h)) && s->i.s_cnt++)
		{				
			if (s->map[s->t.t1 + s->i.v][s->t.t2 + s->i.h] == 'K'\
				|| s->map[s->t.t1 + s->i.v][s->t.t2 + s->i.h] == 'E')
				ft_exit("GAME OWER!", 0);
			if (s->map[s->t.t1 + s->i.v][s->t.t2 + s->i.h] == 'C' && \
														s->i.c_cnt++)
				s->i.c_flag = 1;
			s->map[s->t.t1][s->t.t2] = '0';
			s->t.t1 += s->i.v;
			s->t.t2 += s->i.h;
			s->map[s->t.t1][s->t.t2] = 'P';
			break ;
		}
		else
			s->t.t2++;
		if (!s->map[s->t.t1][s->t.t2] && ++s->t.t1)
			s->t.t2 = 0;
	}
	s->i.v = 0;
	s->i.h = 0;
}

void	create_gameground(t_struct *s, int x, int y)
{
	while (s->map[y])
	{
		if (s->map[y][x] == '1')
			draw_image(s, s->gameground, s->wall, 0);
		else if (s->map[y][x] == 'E')
			draw_image(s, s->gameground, s->exit, 0);
		else if (s->map[y][x] == 'C')
			draw_image(s, s->gameground, s->collectible, 0);
		else if (s->map[y][x] == 'K')
			draw_enemy(s);
		else if (s->map[y][x] == 'P')
			draw_player_movements(s);
		else if (s->map[y][x])
			draw_image(s, s->gameground, NULL, COLOR);
		s->i.x = ++x * s->wall->w;
		if (!s->map[y][x])
		{
			x = 0;
			s->i.x = 0;
			s->i.y = ++y * s->wall->h;
		}
	}
	s->cnt++;
	s->i.y = 0;
	s->i.only_one_plyaer = 0;
}

int	create_game(t_struct *s)
{
	create_gameground(s, 0, 0);
	draw_panel(s, s->gameground, 0x00666699);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->gameground->ptr, 0, 0);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
	s->t.steps = ft_itoa(s->i.s_cnt);
	s->t.collect = ft_itoa(s->i.c_cnt);
	mlx_string_put (s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, s->t.steps);
	mlx_string_put (s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, s->t.collect);
	mlx_do_sync (s->mlx_ptr);
	return (0);
}
