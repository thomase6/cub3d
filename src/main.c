#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		data;
	t_map		map;
	t_player	player;

	ft_bzero(&data, sizeof(data));
	// parser
	if (parser(data, ac, av) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	// mlx
	return (EXIT_SUCCESS);
}

// TODO 
/*
- First make the map file
- the map file location should be the second argument of av so av[1]
- Then we have to make sure it's a valid file name 
- Once the validation happens we have to read the file using getnextline
- extract the 3 different types of information from the file (the textures, the colors and the map information including the player location in the map.)
- 4 files: parser, parse color, parse texture, parse map.

*/