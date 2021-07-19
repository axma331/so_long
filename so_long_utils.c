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
	return (s->tmp);
}
void	init_xpm_images(t_struct *s)
{

	s->pleer = init_mlx_new_or_xpm_file_to_image(s, LION, 0, 0);
	s->item = init_mlx_new_or_xpm_file_to_image(s, ITEM, 0, 0);
	
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

void creat_image(t_struct *s, t_xpm *date)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while(x < s->wall->width)
	{
		if (!date)
			my_mlx_pixel_put(s->tmp, x + s->x_pos, y + s->y_pos, CLR);
		else
			my_mlx_pixel_put(s->tmp, x + s->x_pos, y + s->y_pos, image_pixel_get(date, x, y));
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


void *create_background(t_struct *s, char **map, int x, int y, int color)
{
	x = 0;
	y = 0;

	s->tmp = init_mlx_new_or_xpm_file_to_image(s, NULL, s->x, s->y);
	printf("%d %p %d %d %d %d %d\n", (int)s->wall->addr, s->wall->ptr, s->wall->bits_per_pixel, s->wall->line_length, s->wall->endian, s->wall->width, s->wall->heigth);

	while (map[y][x])
	{
		if (map[y][x] == '1')
		{
			creat_image(s, s->wall);
			s->x_pos = ++x * s->wall->width;
			printf("i: %3d|j: %3d|x_pos: %3d|y_pos: %d\n", x, y, s->x_pos, s->y_pos);
		}
		// else if (map[y][x] == 'P')
		// {
		// 	creat_image(s, s->pleer);
		// 	s->x_pos = ++x * s->wall->width;
		// }
		// else if (map[y][x] == 'C')
		// {
		// 	creat_image(s, s->item);
		// 	s->x_pos = ++x * s->wall->width;
		// }
		// else if (map[y][x] == 'E')
		// {
		// 	creat_image(s, s->item);
		// 	s->x_pos = ++x * s->wall->width;
		// }
		else if (map[y][x] == '0')
		{
			creat_image(s, NULL);
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
	// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->tmp->ptr, 0, 0);
	return (s->tmp);
}
