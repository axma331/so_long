#include "so_long.h"

void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	image_pixel_get(t_xpm *data, int x, int y)
{
	return (*(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))));
}

void creat_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while(x < s->wall->width)
	{
		if (!sorc)
			my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, color);
		else
		{
			if((sorc == s->item || sorc == s->player || sorc == s->exit) && (image_pixel_get(sorc, x, y)) < 0)
				my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, COLOR);
			else
			my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, image_pixel_get(sorc, x, y));
		}
		if (++x == s->wall->width && ++y)
		{
			if (y == s->wall->heigth)
			{
				y = 0;
				break;
			}
			x = 0;
		}
	}

}

void create_background(t_struct *s)
{
	int x = 0;
	int y = 0;
	s->background = init_mlx_xpm_file_to_img_or_new_img(s, NULL, s->x, s->y);
	while (s->map[y])
	{
		if (s->map[y][x] == '1')
		{
			creat_image(s, s->background, s->wall, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else if (s->map[y][x])
		{
			creat_image(s, s->background, NULL, COLOR);
			s->x_pos = ++x * s->wall->width;
		}
		if (!s->map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}

void create_frontround(t_struct *s)
{
	int x = 0;
	int y = 0;

	s->x_pos = 0;
	s->y_pos = 0;
	while (s->map[y])
	{
		// if (s->map[y][x] == 'E')
		// {
		// 	creat_image(s, s->background, s->exit, 0);
		// 	s->x_pos = ++x * s->exit->width;
		// }
		if (s->map[y][x] == 'P')
		{
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player->ptr, s->x_pos, s->y_pos);
			// creat_image(s, s->background, s->player, 0);
			// s->player->x_pos = s->x_pos + 0.5;
			// s->player->y_pos = s->y_pos + 0.5;
			// s->map[y][x] = '0';
			s->x_pos = ++x * s->wall->width;
		}
		else if (s->map[y][x] == 'C')
		{
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->item->ptr, s->x_pos, s->y_pos);
			// creat_image(s, s->background, s->item, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else
			s->x_pos = ++x * s->wall->width;
		if (!s->map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}

void up_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y - 1][x] != '1')
			{
				s->map[y][x] = '0';
				s->map[--y][x] = 'P';
				break ;
			}
		}
		else
			x++;
		if (!s->map[y][x] && y++)
			x = 0;
	}
}
void left_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y][x - 1] != '1')
			{
				s->map[y][x] = '0';
				s->map[y][--x] = 'P';
				break ;
			}
		}
		else
			x++;
		if (!s->map[y][x] && y++)
			x = 0;
	}
}

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
	{
		up_player(s);
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->background->ptr, 0, 0);
		create_frontround(s);
	}
	if (keycode == LEFT)
	{
		left_player(s);
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->background->ptr, 0, 0);
		create_frontround(s);
	}

	return(printf("%i\n", keycode));

}

void put_game(t_struct *s)
{
	create_frontround(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->background->ptr, 0, 0);
}