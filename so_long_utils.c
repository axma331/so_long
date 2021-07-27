#include "so_long.h"

void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width, int height)
{
	t_xpm *img;

	img = (t_xpm *)ft_calloc(1, sizeof (t_xpm));
	if (!img)
		ft_exit("Memory allocation failure for img!", 1);
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

int	pixel_get(t_xpm *data, int x, int y)
{
	return (*(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))));
}

int	ft_close(int keycode, t_struct *s)
{
	ft_exit("The window is closed!", 0);
	return (0);
}