#include "so_long.h"
#include <stdio.h>

int	key_hook(int keycode, t_struct *vars)
{
	return(printf("%i\n", keycode));
}

int	closse(int keycode, t_struct *s)
{
	return (mlx_destroy_window(s->mlx_ptr, s->win_ptr));
}

int main(int argc, char **argv)
{
	t_struct s;
	char **map;

	ft_bzero (&s, sizeof(t_struct));
	map = init_map(argv);
	s.mlx_ptr = mlx_init();
	init_xpm_images(&s);
	s.win_ptr = init_mlx_new_window(&s, map);
	create_background(&s, map);
	create_frontround(&s, map);
	mlx_put_image_to_window(s.mlx_ptr, s.win_ptr, s.background->ptr, 0, 0);
	
	
	printf("Tptr: %14p| addr: %14p| bpp:%3d| line_length:%4d| width:%3d| heigth:%3d\n", s.tmp->ptr, s.tmp->addr, s.tmp->bits_per_pixel, s.tmp->line_length, s.tmp->width, s.tmp->heigth);
	printf("Bptr: %14p| addr: %14p| bpp:%3d| line_length:%4d| width:%3d| heigth:%3d\n", s.background->ptr, s.background->addr, s.background->bits_per_pixel, s.background->line_length, s.background->width, s.background->heigth);
	// mlx_loop_hook(s.mlx_ptr, )
	mlx_loop(s.mlx_ptr);
	return (0);
}
