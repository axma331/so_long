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
	printf("Hello from key_hook!\n");
}

int main(int argc, char **argv)
{
	t_data img;
	t_vars vars;
	void *mlx_ptr;
	void *win_ptr;
	int x = 800;
	int y = 600;
	int color = 0x00009999;
	
	int fd;
	char buff[101];
	fd = open("map.bep", O_RDONLY);
	read (fd, buff, sizeof(buff));
	buff[sizeof(buff) - 1] = '\0';
	printf ("%s", buff);
	
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, x, y, "so_long"); /*Запуск окна*/

	img.img = mlx_new_image(mlx_ptr, x, y);
	int i = 5;
	int j = 5;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while(++i < x - 5)
	{
		my_mlx_pixel_put(&img, i, j, color);
		if (i == x - 6 && ++j < y - 5)
			i = 5;
	}
	mlx_put_image_to_window(mlx_ptr,win_ptr, img.img, 0, 0);
	mlx_string_put(mlx_ptr, win_ptr, 5, 5, color<<2*8, "string");
	mlx_loop(mlx_ptr);

	// mlx_ptr = mlx_init();
	// vars.mlx_ptr = mlx_init();
	// vars.win_ptr = mlx_new_window(mlx_ptr, x, y, "so_long"); /*Запуск окна*/
	// mlx_key_hook(vars.win_ptr, key_hook, &vars);
	// mlx_loop(vars.mlx_ptr);


	// printf("%s , %d, %d, %d", img.img, img.bits_per_pixel, img.line_length, img.endian);
	return (0);
}