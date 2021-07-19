#include "so_long.h"

char	**init_map(char **map)
{
	int fd;
	char *line;
	char **tmp;
	int ret;
	int i;
	int j;

	map = (char **)ft_calloc(2, sizeof(char *));
	if (!map)
		exit (1);
	ret = 1;
	i = 0;
	fd = open("map.bep", O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			exit (1);
		map[i++] = line;
		tmp = map;
		map = (char **)ft_calloc(2 + i, sizeof(char *));
		if (!map)
			exit (1);
			j = -1;
		while(tmp[++j])
			map[j] = tmp[j];
		free(tmp);
	}
	return (map);
}

void	*init_mlx_new_or_xpm_file_to_image(t_struct *s, char *xpm_file, int width, int height)
{
	s->tmp = (t_xpm *)ft_calloc(1, sizeof (t_xpm));
	if (!s->tmp)
		ft_exit("memerr", 1);
	if (!xpm_file)
		s->tmp->ptr = mlx_new_image(s->mlx_ptr, width, height);
	else
		s->tmp->ptr = mlx_xpm_file_to_image(s->mlx_ptr, xpm_file, &s->tmp->width, &s->tmp->heigth);
	s->tmp->addr = mlx_get_data_addr(s->tmp->ptr, &s->tmp->bits_per_pixel, &s->tmp->line_length, &s->tmp->endian);
	printf("%d %p %d %d %d %d %d\n", (int)s->tmp->addr, s->tmp->ptr, s->tmp->bits_per_pixel, s->tmp->line_length, s->tmp->endian, s->tmp->width, s->tmp->heigth);
	return (s->tmp);
}

void	*init_mlx_new_window(t_struct *s, char **map, char *xpm_file)
{
	int x;
	int x_cnt;
	int y_cnt;

	x = 0;
	x_cnt = 0;
	y_cnt = 0;
	s->wall = init_mlx_new_or_xpm_file_to_image(s, xpm_file, s->x, s->y);
	while (map[y_cnt][x])
	{
		if (map[y_cnt][x])
			x_cnt++;
		if (!map[y_cnt][++x] && ++y_cnt)
			x = 0;
	}
	s->x = x_cnt / y_cnt * s->wall->width;
	s->y = y_cnt * s->wall->heigth;
	return (mlx_new_window(s->mlx_ptr, s->x, s->y, "so_long"));
}

void creat_floor(t_struct *s, int color)
{
	int t1;
	int t2;

	t1 = s->x_pos;
	t2 = s->y_pos;
	while(s->x_pos < t1 + s->wall->width)
	{
		my_mlx_pixel_put(s->tmp, s->x_pos, s->y_pos, color);
		if (++s->x_pos == t1 + s->wall->width && ++s->y_pos)
		{
			if (s->y_pos == t2 + s->wall->heigth)
			{
				s->y_pos = t2;
				printf("x: %3d|y: %d |x_pos: %3d|y_pos: %d\n", t1, t2, s->x_pos, s->y_pos);
				break;
			}
			s->x_pos = t1;
		}
	}
}

void *create_background(t_struct *s, char **map, int x, int y, int color)
{
	x = 0;
	y = 0;
	int c = 9;

	s->tmp = init_mlx_new_or_xpm_file_to_image(s, NULL, s->x, s->y);
	printf("%d %p %d %d %d %d %d\n", (int)s->wall->addr, s->wall->ptr, s->wall->bits_per_pixel, s->wall->line_length, s->wall->endian, s->wall->width, s->wall->heigth);

	while (map[y][x])
	{
		// printf("x1:%3d|y1:%d |x_pos: %3d|y_pos: %d\n", x, y, s->x_pos, s->y_pos);
		if (map[y][x] == '1')
		{
			creat_floor(s, 0x00FF00FF);
			x++;
										// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->wall->ptr, s->wall->width * x, s->wall->heigth * y);
		}
		else if (map[y][x] == '0')
		{
			creat_floor(s, 0x000000FF);
			x++;
										// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->wall->ptr, s->wall->width * x, s->wall->heigth * y);
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
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->tmp->ptr, 0, 0);
	return (s->tmp);
}

void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void *create_background(t_struct *s, int b_lt, int b_up, int color)
// {
	// t_data *img;
// 
	// int b_rt;
	// int b_dw;
	// b_rt = b_lt;
	// b_dw = b_up;
	// img = (t_data *)malloc(sizeof(t_data));
	// if (!img)
	// 	ft_exit("background error", 1);
	// img->img_ptr = mlx_new_image(s->mlx_ptr, s->x, s->y);
	// img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	// if ((b_lt > s->x/2) || (b_up > s->y/2))
	// 	return (0);
	// while(b_lt <= s->x - b_rt)
	// {
	// 	my_mlx_pixel_put(img, b_lt, b_up, color);
	// 	if (b_lt == s->x - b_rt)
	// 	{
	// 		if (b_up == s->y - b_dw)
	// 			break;
	// 		b_up++;
	// 		b_lt = b_rt;
	// 	}
	// 	else
	// 		b_lt++;
	// }
	// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, img->img_ptr, 0, 0);
	// free(img);
	// return (img);
// }