#include "so_long.h"

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
		s->info.v = -1;
	else if (keycode == DOWN)
		s->info.v = 1;
	if (keycode == LEFT)
		s->info.h = -1;
	if (keycode == RIGHT)
		s->info.h = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		ft_exit("The window is closed!", 0);
	}
	ft_bzero(&s->t, sizeof(t_temp));
	moving_player(s);
	s->info.v = 0;
	s->info.h = 0;
	return (0);
}

void	moving_player(t_struct *s)
{
	while (s->map[s->t.t1])
	{
		if (s->map[s->t.t1][s->t.t2] == 'P' && \
		(s->map[s->t.t1 + s->info.v][s->t.t2 + s->info.h] != '1' && \
							(s->info.v || s->info.h)))
		{				
			if (s->map[s->t.t1 + s->info.v][s->t.t2 + s->info.h] == 'K'\
				|| s->map[s->t.t1 + s->info.v][s->t.t2 + s->info.h] == 'E')
				ft_exit("GAME OWER!", 0);
			if (s->map[s->t.t1 + s->info.v][s->t.t2 + s->info.h] == 'C' && \
														s->info.c_cnt++)
				s->info.c_flag = 1;
			s->map[s->t.t1][s->t.t2] = '0';
			s->t.t1 += s->info.v;
			s->t.t2 += s->info.h;
			s->map[s->t.t1][s->t.t2] = 'P';
			s->info.s_cnt++;
			break ;
		}
		else
			s->t.t2++;
		if (!s->map[s->t.t1][s->t.t2] && ++s->t.t1)
			s->t.t2 = 0;
	}
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
		s->info.x = ++x * s->wall->w;
		if (!s->map[y][x])
		{
			x = 0;
			s->info.x = 0;
			s->info.y = ++y * s->wall->h;
		}
	}
	s->cnt++;
	s->info.y = 0;
	s->info.only_one_plyaer = 0;
}

int	create_game(t_struct *s)
{
	create_gameground(s, 0, 0);
	draw_panel(s, s->gameground, 0x00666699);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->gameground->ptr, 0, 0);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
	s->t.steps = ft_itoa(s->info.s_cnt);
	s->t.collect = ft_itoa(s->info.c_cnt);
	mlx_string_put (s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, s->t.steps);
	mlx_string_put (s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, s->t.collect);
	mlx_do_sync (s->mlx_ptr);
	return (0);
}
