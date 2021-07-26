#include "so_long.h"

void counting_panel(t_struct *s, t_xpm *dest, int color)
{
	int x;
	int y;
	int l;
	
	x = 0;
	y = 0;
	if (s->pos.steps_cnt < 100)
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
		{
			creat_image(s, s->gameground, s->wall, 0);
			s->pos.x = ++x * s->wall->width;
		}
        else if (s->map[y][x] == 'E')
		{
			creat_image(s, s->gameground, s->exit, 0);
			s->pos.x = ++x * s->exit->width;
		}
		else if (s->map[y][x] == 'P')
		{
            player_movements(s);
			s->pos.player_x = s->pos.x;
			s->pos.player_y = s->pos.y;
			s->pos.x = ++x * s->player[0]->width;
		}
		else if (s->map[y][x] == 'C')
		{
			creat_image(s, s->gameground, s->collectible, 0);
			s->pos.x = ++x * s->collectible->width;
		}
		else if (s->map[y][x] == 'K')
		{
			enemy_movements(s);
			s->pos.player_x = s->pos.x;
			s->pos.player_y = s->pos.y;
			s->pos.x = ++x * s->enemy[0]->width;
		}
		else if (s->map[y][x])
		{
			creat_image(s, s->gameground, NULL, COLOR);
			s->pos.x = ++x * s->wall->width;
		}
		if (!s->map[y][x])
		{
			x = 0;
			s->pos.x = x * s->wall->width;
			s->pos.y = ++y * s->wall->heigth;
		}
	}
    s->pos.y = 0;
}

int put_game(t_struct *s)
{

        create_gameground(s);
        counting_panel(s, s->gameground, 0x00666699);
        mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->gameground->ptr, 0, 0);
        mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
        mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
        mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, ft_itoa(s->pos.steps_cnt));
        mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, ft_itoa(s->pos.collectible_cnt));
        mlx_do_sync(s->mlx_ptr);
	return(0);
}