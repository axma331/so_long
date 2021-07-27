#include "so_long.h"

void	*init_mlx_img(t_struct *s, char *xpm, int width, int height)
{
	t_xpm	*img;

	img = (t_xpm *)ft_calloc(1, sizeof (t_xpm));
	if (!img)
		ft_exit("Memory allocation failure for img!", 1);
	if (!xpm)
		img->ptr = mlx_new_image(s->mlx_ptr, width, height);
	else
		img->ptr = mlx_xpm_file_to_image(s->mlx_ptr, xpm, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->ll, &img->endian);
	return (img);
}

void	my_mlx_pixel_put(t_xpm *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	pixel_get(t_xpm *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + \
		(y * data->ll + x * (data->bpp / 8))));
}

int	ft_close(int keycode, t_struct *s)
{
	ft_exit("The window is closed!", 0);
	return (0);
}

void	pars_mapname(t_temp t, int argc, char **argv)
{
	int		i;
	char	*tmp;

	tmp = ".bep";
	if (argc == 2)
	{
		t.t1 = ft_strlen(argv[1]);
		t.t2 = ft_strlen(tmp);
		if ((ft_strncmp(&argv[1][t.t1 - t.t2], tmp, t.t2)))
			ft_exit("Incorrect name map!", 1);
	}
	else
		ft_exit("Incorrect arguments!", 1);
}
