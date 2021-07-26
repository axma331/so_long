#include "so_long.h"

int main(int argc, char **argv)
{
	t_struct s;

	ft_bzero (&s, sizeof(t_struct));
	s.map = init_map(argv[1]);
	s.mlx_ptr = mlx_init();
    init_idle_images(&s);
    s.win_ptr = init_mlx_new_window(&s);
	mlx_loop_hook(s.mlx_ptr, put_game, &s);
    mlx_key_hook(s.win_ptr, key_hook, &s);
    mlx_hook(s.win_ptr, 17, 1L<<2, &ft_close, &s);
    mlx_loop(s.mlx_ptr);
    return (0);
}