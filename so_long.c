#include "so_long.h"
#include <stdio.h>

int	closse(int keycode, t_struct *s)
{
	return (mlx_destroy_window(s->mlx_ptr, s->win_ptr));
}

int main(int argc, char **argv)
{
	t_struct s;
	char **map;

	ft_bzero (&s, sizeof(t_struct));
	s.map = init_map(argv);
	s.mlx_ptr = mlx_init();
	init_xpm_images(&s);
	s.win_ptr = init_mlx_new_window(&s);

	create_background(&s);
	mlx_put_image_to_window(s.mlx_ptr, s.win_ptr, s.background->ptr, 0, 0);
	create_frontround(&s);
	mlx_string_put(s.mlx_ptr, s.win_ptr, 0, 0, 0x00FF0000, "Steps: ");
	mlx_string_put(s.mlx_ptr, s.win_ptr, 70, 0, 0x00FF0000, ft_itoa(s.steps));

	// mlx_loop_hook(s.mlx_ptr, mlx_key_hook, &s);
	mlx_key_hook(s.win_ptr, key_hook, &s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
