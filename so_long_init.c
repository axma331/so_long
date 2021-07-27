#include "so_long.h"

void	init_map(char *filmane, t_struct *s)
{
	int		fd;
	char	*line;

	s->map = (char **)ft_calloc(2, sizeof(char *));
	if (!s->map)
		ft_exit("Memory allocation failure!", 1);
	s->t.ret = 1;
	fd = open(filmane, O_RDONLY);
	while (s->t.ret != 0)
	{
		s->t.ret = get_next_line(fd, &line);
		if (s->t.ret == -1)
			ft_exit("Error filename!", 1);
		s->map[s->t.t1++] = line;
		s->t.mas = s->map;
		s->map = (char **)ft_calloc(2 + s->t.t1, sizeof(char *));
		if (!s->map)
			exit (1);
		s->t.t2 = -1;
		while (s->t.mas[++s->t.t2])
			s->map[s->t.t2] = s->t.mas[s->t.t2];
		free(s->t.mas);
	}
	checking_map(s);
	close(fd);
}

void	checking_map(t_struct *s)
{
	ft_bzero(&s->t, sizeof(t_temp));
	while (s->map[s->t.t1])
	{
		if (!s->map[s->t.t1][s->t.t2 - 1])
			while (s->map[s->t.t1][s->t.t2] == '1')
				s->t.t2++;
		if (!s->map[s->t.t1][s->t.t2] && ++s->t.t1)
		{
			if (s->t.t2 < 4)
				ft_exit("Map is incorrect!", 1);
			s->t.t2 = 0;
		}
		else
			ft_exit("Map is incorrect!", 1);
		checking_map_first_line(s);
	}
	if (s->t.t1 < 4 )
		ft_exit("Map is incorrect!", 1);
}

void	checking_map_first_line(t_struct *s)
{
	while (s->map[s->t.t1] && s->map[s->t.t1 - 1][s->t.t2])
	{
		if ((s->map[s->t.t1][s->t.t2] != '1' && (!s->map[s->t.t1 + 1] || \
		!s->map[s->t.t1][s->t.t2 - 1] || !s->map[s->t.t1][s->t.t2 + 1])) || \
		(s->map[s->t.t1][s->t.t2] == '1' && !s->map[s->t.t1][s->t.t2 + 1] && \
		s->map[s->t.t1 - 1][s->t.t2 + 1]))
			ft_exit("Map is incorrect!", 1);
		s->t.t2++;
	}
}

void	init_idle_images(t_struct *s)
{
	s->wall = init_mlx_img(s, "xpm/tree.xpm", 0, 0);
	s->collectible = init_mlx_img(s, "xpm/collectible.xpm", 0, 0);
	s->exit = init_mlx_img(s, "xpm/exit.xpm", 0, 0);
	s->enemy[0] = init_mlx_img(s, "xpm/enemy_1.xpm", 0, 0);
	s->enemy[1] = init_mlx_img(s, "xpm/enemy_2.xpm", 0, 0);
	s->enemy[2] = init_mlx_img(s, "xpm/enemy_3.xpm", 0, 0);
	s->enemy[3] = init_mlx_img(s, "xpm/enemy_4.xpm", 0, 0);
	s->player[0] = init_mlx_img(s, "xpm/player_1.xpm", 0, 0);
	s->player[1] = init_mlx_img(s, "xpm/player_2.xpm", 0, 0);
	s->player[2] = init_mlx_img(s, "xpm/player_3.xpm", 0, 0);
	s->player[3] = init_mlx_img(s, "xpm/player_4.xpm", 0, 0);
	s->player[4] = init_mlx_img(s, "xpm/player_5.xpm", 0, 0);
	s->player[5] = init_mlx_img(s, "xpm/player_6.xpm", 0, 0);
	s->player_a[0] = init_mlx_img(s, "xpm/player_attak_1.xpm", 0, 0);
	s->player_a[1] = init_mlx_img(s, "xpm/player_attak_2.xpm", 0, 0);
	s->player_a[2] = init_mlx_img(s, "xpm/player_attak_3.xpm", 0, 0);
	s->player_a[3] = init_mlx_img(s, "xpm/player_attak_4.xpm", 0, 0);
}

void	*init_mlx_new_window(t_struct *s)
{
	ft_bzero(&s->t, sizeof(t_temp));
	while (s->map[s->y])
	{
		if (s->map[s->y][s->t.t1++])
			if (s->t.t1 > s->x)
				s->x = s->t.t1;
		if (!s->map[s->y][s->t.t1] && ++s->y)
			s->t.t1 = 0;
	}
	s->x *= s->wall->w;
	s->y *= s->wall->h;
	s->gameground = init_mlx_img(s, NULL, s->x, s->y);
	return (mlx_new_window(s->mlx_ptr, s->x, s->y, "so_long"));
}
