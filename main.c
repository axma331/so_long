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

int	key_hook(int keycode, t_data *vars)
{
	return(printf("Hello from key_hook!\n"));
}

int main(int argc, char **argv)
{
	t_struct s;
	t_data img;
	// s.img = (t_data *)malloc(sizeof(t_data));
	int x = 800;
	int y = 600;
	int color = 0x00009999;
	
	int fd;
	char buff[101];
	fd = open("map.bep", O_RDONLY);
	read (fd, buff, sizeof(buff));
	buff[sizeof(buff) - 1] = '\0';
	printf ("%s", buff);
	
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, x, y, "so_long"); /*Запуск окна*/
	s.img = &img;
	s.img->img_ptr = mlx_new_image(s.mlx_ptr, x, y);
	int i = 5;
	int j = 5;
	s.img->addr = mlx_get_data_addr(s.img->img_ptr, &s.img->bits_per_pixel, &s.img->line_length, &s.img->endian);
	while(++i < x - 5)
	{
		my_mlx_pixel_put(s.img, i, j, color);
		if (i == x - 6 && ++j < y - 5)
			i = 5;
	}
	mlx_put_image_to_window(s.mlx_ptr,s.win_ptr, s.img->img_ptr, 0, 0);
	mlx_key_hook(s.win_ptr, key_hook, &s);
	mlx_string_put(s.mlx_ptr, s.win_ptr, 5, 5, color<<16, "string");
	mlx_loop(s.mlx_ptr);
	return (0);
}