#include "so_long.h"

char	**init_map(char **map)
{
	int fd;
	char *line;
	char **tmp;
	int ret;
	int i;
	int j;

	map = (char **)ft_calloc(2, sizeof(char *));
	if (!map)
		exit (1);
	ret = 1;
	i = 0;
	fd = open("map.bep", O_RDONLY);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			exit (1);
		map[i++] = line;
		tmp = map;
		map = (char **)ft_calloc(2 + i, sizeof(char *));
		if (!map)
			exit (1);
			j = -1;
		while(tmp[++j])
			map[j] = tmp[j];
		free(tmp);
	}
	return (map);
}
