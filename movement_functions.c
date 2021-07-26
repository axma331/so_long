#include "so_long.h"

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
		s->pos.vertical = -1;
	else if (keycode == DOWN)
		s->pos.vertical = 1;
	if (keycode == LEFT)
		s->pos.horizontal = -1;
	if (keycode == RIGHT)
		s->pos.horizontal = 1;
	moving_player(s);
	return(printf("%i\n", keycode));
}

void moving_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y + s->pos.vertical][x + s->pos.horizontal] != '1')
			{
				
				if (s->map[y + s->pos.vertical][x + s->pos.horizontal] == 'K')
					ft_exit("GAME OWER!", 1);
				if (s->map[y + s->pos.vertical][x + s->pos.horizontal] == 'E')
					ft_exit("GAME OWER!", 0);
				if (s->map[y + s->pos.vertical][x + s->pos.horizontal] == 'C')
					s->pos.collectible_cnt++;
				s->map[y][x] = '0';
				s->map[y += s->pos.vertical][x += s->pos.horizontal] = 'P';
				s->pos.steps_cnt++;
			}
			break ;
		}
		else
			x++;
		if (!s->map[y][x] && ++y)
			x = 0;
	}
	s->pos.vertical = 0;
	s->pos.horizontal = 0;
}

void player_movements(t_struct *s)
{
	s->pos.p_f  =  (s->cnt % (6 * SPEED )) / SPEED;
	creat_image(s, s->gameground, s->player[s->pos.p_f], 0);
	s->cnt++;
}

void enemy_movements(t_struct *s)
{	
	s->pos.e_f  =  (s->cnt % (4 * SPEED )) / SPEED;
	creat_image(s, s->gameground, s->enemy[s->pos.e_f], 0);
	s->cnt++;
}
