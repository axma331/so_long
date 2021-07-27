#include "so_long.h"

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
		ft_exit("The window is closed!", 0);
	}
	moving_player(s);
	return(printf("%i\n", keycode));
}

void moving_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y + s->info.vertical][x + s->info.horizontal] != '1' && (s->info.vertical || s->info.horizontal))
			{				
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'K')
					ft_exit("GAME OWER!", 1);
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'E')
					ft_exit("GAME OWER!", 0);
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'C')
				{
					s->info.c_flag = 1;
					s->info.collectible_cnt++;
				}
				s->map[y][x] = '0';
				s->map[y += s->info.vertical][x += s->info.horizontal] = 'P';
					s->info.steps_cnt++;
			}
			break ;
		}
		else
			x++;
		if (!s->map[y][x] && ++y)
			x = 0;
	}
	s->info.vertical = 0;
	s->info.horizontal = 0;
}

void create_gameground(t_struct *s, int x, int y)
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
		s->info.x = ++x * s->wall->width;
		if (!s->map[y][x])
		{
			x = 0;
			s->info.x = 0;
			s->info.y = ++y * s->wall->heigth;
		}
	}
	s->cnt++;
	s->info.y = 0;
	s->info.only_one_plyaer = 0;
}

int create_game(t_struct *s)
{
	create_gameground(s, 0, 0);
	draw_panel(s, s->gameground, 0x00666699);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->gameground->ptr, 0, 0);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, ft_itoa(s->info.steps_cnt));
	mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, ft_itoa(s->info.collectible_cnt));
	mlx_do_sync(s->mlx_ptr);
	return(0);
}
