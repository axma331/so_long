#include "so_long.h"

void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width, int height)
{
	t_xpm *img;

	img = (t_xpm *)ft_calloc(1, sizeof (t_xpm));
	if (!img)
		ft_exit("memerr", 1);
	if (!xpm_file)
		img->ptr = mlx_new_image(s->mlx_ptr, width, height);
	else
		img->ptr = mlx_xpm_file_to_image(s->mlx_ptr, xpm_file, &img->width, &img->heigth);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img);
}

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
			my_mlx_pixel_put(dest, x + s->info.x, y + s->info.y, color);
		else
		{
			if((image_pixel_get(sorc, x, y)) < 0)
				my_mlx_pixel_put(dest, x + s->info.x, y + s->info.y, COLOR);
			else
			my_mlx_pixel_put(dest, x + s->info.x, y + s->info.y, image_pixel_get(sorc, x, y));
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
	// if (x == s->wall->width)
	// 	s->info.x += s->wall->width;
}
