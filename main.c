#include "so_long.h"
#include <stdio.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_struct *vars)
{
	return(printf("%i\n", keycode));
}

int	closse(int keycode, t_struct *s)
{
	return (mlx_destroy_window(s->mlx_ptr, s->win_ptr));
}

void create_new_images(t_struct *s, int i, int j, int color)
{
	s->img->img_ptr = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img->addr = mlx_get_data_addr(s->img->img_ptr, &s->img->bits_per_pixel, &s->img->line_length, &s->img->endian);
	while(++i < s->x - 5)
	{
		my_mlx_pixel_put(s->img, i, j, mlx_get_color_value(s->mlx_ptr, color<<6)); /*mlx_get_color_value() ?*/
		if (i == s->x - 6 && ++j < s->y - 5)
			i = 5;
	}
	mlx_put_image_to_window(s->mlx_ptr,s->win_ptr, s->img->img_ptr, 5, 5);
}

int main(int argc, char **argv)
{
	t_struct s;
	t_data img;
	s.img = &img;
	s.x = 800;
	s.y = 600;
	int color = 0x0000FFFF;
	
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, s.x, s.y, "so_long");
	// create_new_images(&s, 0, 0, color);
	s.img->img_ptr = mlx_xpm_file_to_image(s.mlx_ptr, "fon.xpm", &s.x, &s.y);
	mlx_put_image_to_window(s.mlx_ptr,s.win_ptr, s.img->img_ptr, 0, 0);

	s.img->img_ptr = mlx_xpm_file_to_image(s.mlx_ptr, "b.xpm", &s.x, &s.y);
	s.img->addr = mlx_get_data_addr(s.img->img_ptr, &s.img->bits_per_pixel, &s.img->line_length, &s.img->endian);
	mlx_put_image_to_window(s.mlx_ptr,s.win_ptr, s.img->img_ptr, 0 , 0);
	mlx_put_image_to_window(s.mlx_ptr,s.win_ptr, s.img->img_ptr, 0 , 0);

	// mlx_put_image_to_window(s.mlx_ptr,s.win_ptr, s.img->img_ptr, &s.img->addr, 0);
	// s.img->addr = mlx_get_data_addr(s.img->img_ptr, &s.img->bits_per_pixel, &s.img->line_length, &s.img->endian);



	// mlx_string_put(s.mlx_ptr, s.win_ptr, 5, 5, color <<0, "string");

	mlx_loop(s.mlx_ptr);
	return (0);
}

	// int fd;
	// char buff[101];
	// fd = open("map.bep", O_RDONLY);
	// read (fd, buff, sizeof(buff));
	// buff[sizeof(buff) - 1] = '\0';
	// printf ("%s", buff);