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
			my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, image_pixel_get(sorc, x, y));
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

void create_background(t_struct *s, char **map)
{
	int x = 0;
	int y = 0;
	s->background = init_mlx_xpm_file_to_img_or_new_img(s, NULL, s->x, s->y);
	while (map[y][x])
	{
		if (map[y][x] == '1')
		{
			creat_image(s, s->background, s->wall, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else if (map[y][x])
		{
			creat_image(s, s->background, NULL, 0);
			s->x_pos = ++x * s->wall->width;
		}
		if (!map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}

void create_frontround(t_struct *s, char **map)
{
	int x = 0;
	int y = 0;

	s->x_pos = 0;
	s->y_pos = 0;
	while (map[y][x])
	{
		if (map[y][x] == 'E')
		{
			creat_image(s, s->background, s->exit, 0);
			s->x_pos = ++x * s->exit->width;
		}
		if (map[y][x] == 'P')
		{
			creat_image(s, s->background, s->player, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else if (map[y][x] == 'C')
		{
			creat_image(s, s->background, s->item, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else
			s->x_pos = ++x * s->wall->width;
		if (!map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}