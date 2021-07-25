#include "so_long.h"

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

void creat_image(t_struct *s, t_xpm *dest, t_xpm *sorc, int color)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while(x < s->wall->width)
	{
		if (!sorc)
			my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, color);
		else
		{
			// if((sorc == s->item || sorc == s->player || sorc == s->exit) && (image_pixel_get(sorc, x, y)) < 0)
			if((image_pixel_get(sorc, x, y)) < 0)
				my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, COLOR);
			else
			my_mlx_pixel_put(dest, x + s->x_pos, y + s->y_pos, image_pixel_get(sorc, x, y));
		}
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

void background_for_steps(t_struct *s, t_xpm *dest, int color)
{
	int x;
	int y;
	int l;
	
	x = 0;
	y = 0;
	if (s->steps < 100)
		l = 90;
	else
		l = 100;
	while(x < l)
	{
		my_mlx_pixel_put(dest, x , y , color);
		if (++x == l && ++y)
		{
			if (y == 40)
				break;
			x = 0;
		}
	}
}

void create_background(t_struct *s)
{
	int x = 0;
	int y = 0;
	s->background = init_mlx_xpm_file_to_img_or_new_img(s, NULL, s->x, s->y);
	while (s->map[y])
	{
		if (s->map[y][x] == '1')
		{
			creat_image(s, s->background, s->wall, 0);
			s->x_pos = ++x * s->wall->width;
		}
		else if (s->map[y][x])
		{
			creat_image(s, s->background, NULL, COLOR);
			s->x_pos = ++x * s->wall->width;
		}
		if (!s->map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}

void create_frontround(t_struct *s)
{
	int x = 0;
	int y = 0;

	s->x_pos = 0;
	s->y_pos = 0;

	// printf ("Bˆptr: %p| addr: %d| bpp: %2d| line_length:%4d| endian: %d| w:%d| h:%d| x_pos:%.1f| y_pos: %.1f\n", \
	// s->background->ptr, *(unsigned int*)s->background->addr, s->background->bits_per_pixel, s->background->line_length, s->background->endian, s->background->width, s->background->heigth, s->background->x_pos, s->background->y_pos);
	// printf ("Fˆptr: %p| addr: %d| bpp: %2d| line_length:%4d| endian: %d| w:%d| h:%d| x_pos:%.1f| y_pos: %.1f\n", \
	// s->frontround->ptr, *(unsigned int*)s->frontround->addr, s->frontround->bits_per_pixel, s->frontround->line_length, s->frontround->endian, s->frontround->width, s->frontround->heigth, s->frontround->x_pos, s->frontround->y_pos);

	// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->background->ptr, 0, 0);
	// create_background(s);
	while (s->map[y])
	{
		if (s->map[y][x] == 'E')
		{
			// creat_image(s, s->background, s->exit, 0);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->exit->ptr, s->x_pos, s->y_pos);
			s->x_pos = ++x * s->exit->width;
		}
		if (s->map[y][x] == 'P')
		{
			// creat_image(s, s->background, s->player1, 0);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player1->ptr, s->x_pos - 10, s->y_pos);
			s->player1->x_pos = s->x_pos;
			s->player1->y_pos = s->y_pos;
			s->x_pos = ++x * s->wall->width;
		}
		else if (s->map[y][x] == 'C')
		{
			creat_image(s, s->background, s->item, 0);
			// mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->item->ptr, s->x_pos, s->y_pos);
			s->x_pos = ++x * s->wall->width;
		}
		// else if (s->map[y][x] == 'S')
		// {
		// 	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton1->ptr, s->x_pos, s->y_pos);
		// 	s->skeleton1->x_pos = s->x_pos;
		// 	s->skeleton1->y_pos = s->y_pos;
		// 	s->x_pos = ++x * s->wall->width;
		// }
		else
			s->x_pos = ++x * s->wall->width;
		if (!s->map[y][x])
		{
			x = 0;
			s->x_pos = x * s->wall->width;
			s->y_pos = ++y * s->wall->heigth;
		}
	}
}


void moving_player(t_struct *s)
{
	int x = 0;
	int y = 0;

	while (s->map[y])
	{
		if (s->map[y][x] == 'P')
		{
			if (s->map[y + s->v][x + s->g] != '1')
			{
				
				// if (s->map[y + s->v][x + s->g] == 'E')
				// {
				// 	sleep (2);
				// 	ft_exit("GAME OWER!", 0);
				// }
				if (s->map[y + s->v][x + s->g] == 'C')
					s->collec++;
				s->map[y][x] = '0';
				s->map[y += s->v][x += s->g] = 'P';
					++s->steps;
				printf ("y: %d | x: %d\n", y, x);
			}
			break ;
		}
		else
			x++;
		if (!s->map[y][x] && ++y)
			x = 0;
	}
	s->v = 0;
	s->g = 0;
}

void *put_game(t_struct *s)
{
	moving_player(s);
	// background_for_steps(s, s->background, 0x00666699);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->background->ptr, 0, 0);
	create_frontround(s);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0x0033CCFF, "Steps:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 20, 0x0033CCFF, "Items:");
	mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 0, 0x0033CCFF, ft_itoa(s->steps));
	mlx_string_put(s->mlx_ptr, s->win_ptr, 70, 20, 0x0033CCFF, ft_itoa(s->collec));
	return(s);
}

int	key_hook(int keycode, t_struct *s)
{
	if (keycode == UP)
		s->v = -1; /* Заменить на speed и включить в структуру*/
	else if (keycode == DOWN)
		s->v = 1;
	if (keycode == LEFT)
		s->g = -1;
	if (keycode == RIGHT)
		s->g = 1;
	// printf ("v: %d | g: %d\n", s->v, s->g);
	put_game(s);
	return(printf("%i\n", keycode));
}

int player_movements(t_struct *s)
{
		s->cnt++;
		if (s->cnt == 2000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player1->ptr, s->player1->x_pos, s->player1->y_pos);
			}
		if (s->cnt == 4000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player2->ptr, s->player1->x_pos, s->player1->y_pos);
		}
		if (s->cnt == 6000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player3->ptr, s->player1->x_pos, s->player1->y_pos);
		}
		if (s->cnt == 8000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player4->ptr, s->player1->x_pos, s->player1->y_pos);
		}
		if (s->cnt == 10000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player5->ptr, s->player1->x_pos, s->player1->y_pos);
		}
		if (s->cnt == 12000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->player1->x_pos, s->player1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->player6->ptr, s->player1->x_pos, s->player1->y_pos);
			s->cnt = 0;
		}
				if (s->cnt == 3000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton1->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			}
		if (s->cnt == 6000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton2->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
		}
		if (s->cnt == 9000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton3->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
		}
		if (s->cnt == 12000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton4->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			s->cnt = 0;
		}
	return (1);
}
int skeleton_movements(t_struct *s)
{
		s->cnt++;
		if (s->cnt == 3000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton1->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			}
		if (s->cnt == 6000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton2->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
		}
		if (s->cnt == 9000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton3->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
		}
		if (s->cnt == 12000){
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->imgground->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->skeleton4->ptr, s->skeleton1->x_pos, s->skeleton1->y_pos);
			s->cnt = 0;
		}
	return (1);
}

void background_for_img(t_struct *s, t_xpm *dest, int color)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	s->imgground = init_mlx_xpm_file_to_img_or_new_img(s, NULL, s->player1->width, s->player1->heigth);

	while(x < 64)
	{
		my_mlx_pixel_put(s->imgground, x , y , color);
		if (++x == 64 && ++y)
		{
			if (y == 64)
				break;
			x = 0;
		}
	}
}