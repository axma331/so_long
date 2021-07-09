#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

typedef struct	s_data
{
	void *img_ptr;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}				t_data;

// typedef struct	s_map
// {
// 	unsigned int RGB;
// 	int	endian;
// }				t_map;

typedef struct	s_struct
{
	int x;
	int y;
	void *mlx_ptr;
	void *win_ptr;
	t_data *img;
}				t_struct;

#endif