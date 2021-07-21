#include "so_long.h"

void	*init_mlx_xpm_file_to_img_or_new_img(t_struct *s, char *xpm_file, int width, int height)
{
	s->tmp = (t_xpm *)ft_calloc(1, sizeof (t_xpm));
	if (!s->tmp)
		ft_exit("memerr", 1);
	if (!xpm_file)
		s->tmp->ptr = mlx_new_image(s->mlx_ptr, width, height);
	else
		s->tmp->ptr = mlx_xpm_file_to_image(s->mlx_ptr, xpm_file, &s->tmp->width, &s->tmp->heigth);
	s->tmp->addr = mlx_get_data_addr(s->tmp->ptr, &s->tmp->bits_per_pixel, &s->tmp->line_length, &s->tmp->endian);
	return (s->tmp);
}

void	init_xpm_images(t_struct *s)
{
	s->wall = init_mlx_xpm_file_to_img_or_new_img(s, WALL, 0, 0);
	s->player = init_mlx_xpm_file_to_img_or_new_img(s, PLAYER, 0, 0);
	s->item = init_mlx_xpm_file_to_img_or_new_img(s, ITEM, 0, 0);
	s->exit = init_mlx_xpm_file_to_img_or_new_img(s, EXIT, 0, 0);
}

void	*init_mlx_new_window(t_struct *s)
{
	int x_cnt;

	x_cnt = 0;
	while (s->map[s->y])
	{
		if (s->map[s->y][x_cnt++])
			if (x_cnt > s->x)
				s->x = x_cnt;
		if (!s->map[s->y][x_cnt] && ++s->y)
			x_cnt = 0;
	}
	s->x *= s->wall->width;
	s->y *= s->wall->heigth;
	return (mlx_new_window(s->mlx_ptr, s->x, s->y, "so_long"));
}
