#include "so_long.h"
#include <stdio.h>

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

void create_new_images(t_struct *s, int b_w, int b_n, int color)
{
	t_data img;
	s->img = &img;

	int b_e = b_w;
	int b_s = b_n;
	s->img->img_ptr = mlx_new_image(s->mlx_ptr, s->x, s->y);
	s->img->addr = mlx_get_data_addr(s->img->img_ptr, &s->img->bits_per_pixel, &s->img->line_length, &s->img->endian);
	while(b_w++ < s->x - b_e)
	{
		my_mlx_pixel_put(s->img, b_w, b_n, color);
		if (b_w == s->x - b_e && b_n++ <= s->y - b_e)
			b_w = b_e;
	}
	mlx_put_image_to_window(s->mlx_ptr,s->win_ptr, s->img->img_ptr, 0, 0);
}

int main(int argc, char **argv)
{
	t_struct s;
	int fd;
	char *line;
	char **str;
	char **tmp;
	int ret;
	int i;
	int j;

	str = (char **)ft_calloc(2, sizeof(char *));
	if (!str)
		exit (1);
	ret = 1;
	i = 0;
	fd = open("map.bep", O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			exit (1);
		str[i++] = line;
		tmp = str;
		str = (char **)ft_calloc(2 + i, sizeof(char *));
		if (!str)
			exit (1);
			j = -1;
		while(tmp[++j])
			str[j] = tmp[j];
		free(tmp);
	}

	// // s.mlx_ptr = mlx_init();
	// // s.win_ptr = mlx_new_window(s.mlx_ptr, s.x, s.y, "so_long");
	// // create_new_images(&s, 32, 64, color);
	// // mlx_loop(s.mlx_ptr);
	return (0);
}

	// for(int j = 0; str[j]; j++)
	// 	printf("%s\n", str[j]);