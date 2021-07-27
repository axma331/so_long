#include "so_long.h"

void	draw_panel(t_game *s, t_xpm *dest, int color)
{
	int	x;
	int	y;
	int	l;

	x = 0;
	y = 0;
	if (s->info.s_cnt < 100)
		l = 90;
	else
		l = 100;
	while (x < l)
	{
		my_mlx_pixel_put(dest, x, y, color);
		if (++x == l && ++y)
		{
			if (y == 40)
				break ;
			x = 0;
		}
	}
}

void	draw_image(t_game *s, t_xpm *dest, t_xpm *sorc, int color)
{
	int	clr;

	ft_bzero(&s->t, sizeof(t_temp));
	while (s->t.t2 < s->wall->w)
	{
		s->t.x = s->t.t2 + s->info.x;
		s->t.y = s->t.t1 + s->info.y;
		if (!sorc)
			my_mlx_pixel_put(dest, s->t.x, s->t.y, color);
		else
		{
			clr = pixel_get(sorc, s->t.t2, s->t.t1);
			if (clr < 0)
				my_mlx_pixel_put(dest, s->t.x, s->t.y, COLOR);
			else
				my_mlx_pixel_put(dest, s->t.x, s->t.y, clr);
		}
		if (++s->t.t2 == s->wall->w && ++s->t.t1)
		{
			if (s->t.t1 == s->wall->h)
				break ;
			s->t.t2 = 0;
		}
	}
}

void	draw_player(t_game *s)
{
	if (s->info.c_flag)
	{
		draw_image(s, s->gameground, \
					s->player_a[(s->info.c_flag++ - 1) / 5], 0);
		if (s->info.c_flag == 20)
			s->info.c_flag = 0;
	}
	else
	{
		s->info.p_flag = (s->cnt % (6 * SPEED)) / SPEED;
		draw_image(s, s->gameground, s->player[s->info.p_flag], 0);
	}
}

void	draw_player_movements(t_game *s)
{
	if (s->info.only_one_plyaer)
		ft_exit_so_long(s, "Error: a lot of players!", 0);
	else
		s->info.only_one_plyaer = 1;
	draw_player(s);
}

void	draw_enemy(t_game *s)
{	
	s->info.e_flag = (s->cnt % (4 * SPEED)) / SPEED;
	draw_image(s, s->gameground, s->enemy[s->info.e_flag], 0);
}
