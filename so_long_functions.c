#include "so_long.h"

void counting_panel(t_struct *s, t_xpm *dest, int color)
{
	int x;
	int y;
	int l;
	
	x = 0;
	y = 0;
	if (s->info.steps_cnt < 100)
		l = 90;
	else
		l = 100;
	while(x < l)
	{
		my_mlx_pixel_put(dest, x , y , color);
		if (++x == l && ++y)
		{
			if (y == 40)
				break;
			x = 0;
		}
	}
}

void create_gameground(t_struct *s)
{
	int x = 0;
	int y = 0;
	while (s->map[y])
	{
		if (s->map[y][x] == '1')
			draw_image(s, s->gameground, s->wall, 0);
		else if (s->map[y][x] == 'E')
			draw_image(s, s->gameground, s->exit, 0);
		else if (s->map[y][x] == 'P')
		{
			if (s->info.only_one_plyaer)
				ft_exit("Error: More player!", 1);
			else
				s->info.only_one_plyaer = 1;
			player_movements(s);
		}
		else if (s->map[y][x] == 'C')
			draw_image(s, s->gameground, s->collectible, 0);
		else if (s->map[y][x] == 'K')
			enemy_movements(s);
		else if (s->map[y][x])
			draw_image(s, s->gameground, NULL, COLOR);
		s->info.x = ++x * s->wall->width;
		if (!s->map[y][x])
		{
			x = 0;
			s->info.x = x * s->wall->width;
			s->info.y = ++y * s->wall->heigth;
		}
	}
	s->cnt++;
	s->info.y = 0;
	s->info.only_one_plyaer = 0;
}

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
		s->info.vertical = -1;
	else if (keycode == DOWN)
		s->info.vertical = 1;
	if (keycode == LEFT)
		s->info.horizontal = -1;
	if (keycode == RIGHT)
		s->info.horizontal = 1;
	if (keycode == ESC)
	{
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
		ft_exit("Win close!", 0);
	}
	moving_player(s);
	return(printf("%i\n", keycode));
}

int put_game(t_struct *s)
{
		create_gameground(s);
		counting_panel(s, s->gameground, 0x00666699);
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->gameground->ptr, 0, 0);
		mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
		mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
		mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, ft_itoa(s->info.steps_cnt));
		mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, ft_itoa(s->info.collectible_cnt));
		mlx_do_sync(s->mlx_ptr);
	return(0);
}

int	ft_close(int keycode, t_struct *s)
{
	ft_exit("Win close!", 0);
	return (0);
}

