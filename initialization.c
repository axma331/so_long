#include "so_long.h"

void *init_map(char *filmane)
{
	int fd;
	char *line;
    char **map;
	char **tmp;
	int ret;
	int i;
	int j;

	map = (char **)ft_calloc(2, sizeof(char *));
	if (!map)
		exit (1);
	ret = 1;
	i = 0;
	fd = open(filmane, O_RDONLY);
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
    return(map);
}

void	init_idle_images(t_struct *s)
{
	s->wall = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/tree.xpm", 0, 0);
    s->collectible = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/collectible.xpm", 0, 0);
	s->exit = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/exit.xpm", 0, 0);
	s->enemy[0] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/skeleton_1.xpm", 0, 0);
	s->enemy[1] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/skeleton_2.xpm", 0, 0);
	s->enemy[2] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/skeleton_3.xpm", 0, 0);
	s->enemy[3] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/skeleton_4.xpm", 0, 0);
	s->player[0] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_1.xpm", 0, 0);
	s->player[1] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_2.xpm", 0, 0);
	s->player[2] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_3.xpm", 0, 0);
	s->player[3] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_4.xpm", 0, 0);
	s->player[4] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_5.xpm", 0, 0);
	s->player[5] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_6.xpm", 0, 0);
	s->player_attak[0] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_attak_1.xpm", 0, 0);
	s->player_attak[1] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_attak_2.xpm", 0, 0);
	s->player_attak[2] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_attak_3.xpm", 0, 0);
	s->player_attak[3] = init_mlx_xpm_file_to_img_or_new_img(s, "xpm/player_attak_4.xpm", 0, 0);
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
    s->gameground = init_mlx_xpm_file_to_img_or_new_img(s, NULL, s->x, s->y);
	return (mlx_new_window(s->mlx_ptr, s->x, s->y, "so_long"));
}
