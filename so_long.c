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
	ft_bzero (&s, sizeof(t_struct));
	char **map;

	map = init_map(argv);
	s.mlx_ptr = mlx_init();
	s.win_ptr = init_mlx_new_window(&s, map, TREE);
	init_xpm_images(&s);

	s.background = create_background(&s, map, 0, 0, 0x00FF0000);
	mlx_put_image_to_window(s.mlx_ptr, s.win_ptr, s.background->ptr, 0, 0);

	// mlx_loop_hook(s.mlx_ptr, )
	mlx_loop(s.mlx_ptr);
	return (0);
}

