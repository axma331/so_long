#include "so_long.h"

void moving_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y + s->info.vertical][x + s->info.horizontal] != '1')
			{				
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'K')
					ft_exit("GAME OWER!", 1);
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'E')
					ft_exit("GAME OWER!", 0);
				if (s->map[y + s->info.vertical][x + s->info.horizontal] == 'C')
				{
					s->info.c_flag = 1;
					s->info.collectible_cnt++;
				}
				s->map[y][x] = '0';
				s->map[y += s->info.vertical][x += s->info.horizontal] = 'P';
				s->info.steps_cnt++;
			}
			break ;
		}
		else
			x++;
		if (!s->map[y][x] && ++y)
			x = 0;
	}
	s->info.vertical = 0;
	s->info.horizontal = 0;
}

void player_movements(t_struct *s)
{
	s->info.p_flag  =  (s->cnt % (6 * SPEED )) / SPEED;
	draw_image(s, s->gameground, s->player[s->info.p_flag], 0);
}

void enemy_movements(t_struct *s)
{	
	s->info.e_flag  =  (s->cnt % (4 * SPEED )) / SPEED;
	draw_image(s, s->gameground, s->enemy[s->info.e_flag], 0);
}

void player_attak(t_struct *s)
{
	s->info.p_flag  =  (s->cnt % (4 * SPEED )) / SPEED;
	draw_image(s, s->gameground, s->player_attak[s->info.p_flag], 0);
	if (s->info.p_flag == 0)
		s->info.c_flag = 0;
}
