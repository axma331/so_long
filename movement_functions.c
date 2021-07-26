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
					s->info.collectible_cnt++;
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
	creat_image(s, s->gameground, s->player[s->info.p_flag], 0);
	s->info.player_x = s->info.x;
	s->info.player_y = s->info.y;
}

void enemy_movements(t_struct *s)
{	
	s->info.e_flag  =  (s->cnt % (4 * SPEED )) / SPEED;
	creat_image(s, s->gameground, s->enemy[s->info.e_flag], 0);
	s->info.enemy_x = s->info.x;
	s->info.enemy_x = s->info.y;
}

// int player_run(t_struct *s)
// {
// 	s->info.tmp = s->info.x;
// 	s->info.p_flag  =  (s->cnt % (8 * SPEED )) / SPEED;
// 	printf("%d\n", s->info.p_flag);
// 	printf("%d\n", s->cnt);
// 	if (s->info.p_flag == 2)
// 		s->info.x = s->info.player_x + 8;
// 	creat_image(s, s->gameground, s->player_run[s->info.p_flag], 0);
// 	if (s->info.x == s->info.tmp)
// 	{
// 		s->info.only_one_plyaer = 1;
// 		return (1);
// 	}
// 	else
// 	{
// 		s->info.player_x = s->info.x;
// 		s->info.player_y = s->info.y;
// 		s->info.x = s->info.tmp;
// 		s->info.only_one_plyaer = 0;
// 	}
// 	return (0);
// }


// void moving_enemy(t_struct *s)
// {
// 	int x = 0;
// 	int y = 0;
// 
// 	while (s->map[y])
// 	{
// 		if (s->map[y][x] == 'K')
// 		{
// 			if (s->map[y + s->pos.vertical][x + s->pos.horizontal] != '1')
// 			{
// 
// 				if (s->map[y + s->pos.vertical][x + s->pos.horizontal] == 'E')
// 					ft_exit("GAME OWER!", 0);
// 				if (s->map[y + s->pos.vertical][x + s->pos.horizontal] == 'C')
// 					s->pos.collectible_cnt++;
// 				s->map[y][x] = '0';
// 				s->map[y += s->pos.vertical][x += s->pos.horizontal] = 'P';
// 				s->pos.steps_cnt++;
// 			}
// 			break ;
// 		}
// 		else
// 			x++;
// 		if (!s->map[y][x] && ++y)
// 			x = 0;
// 	}
// 	s->pos.vertical = 0;
// 	s->pos.horizontal = 0;
// }