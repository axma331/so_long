#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>

typedef struct	s_data
{
	void *img;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}				t_data;

typedef struct	s_vars
{
	void *mlx_ptr;
	void *win_ptr;
}				t_vars;

typedef struct	s_struct
{
	t_data *img;
	t_vars *vars;
}				t_struct;

#endif