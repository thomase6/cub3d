#include "cub3d.h"

void	free_game(t_game *data)
{
	if (data->map.north != NULL)
		free(data->map.north);
	if (data->map.south != NULL)
		free(data->map.south);
	if (data->map.east != NULL)
		free(data->map.east);
	if (data->map.west != NULL)
		free(data->map.west);
	if (data->map.map_grid != NULL)
		free_arr(data->map.map_grid);
}

int	main(int ac, char **av)
{
	t_game		data;
	(void)ac;
	(void)av;
	ft_bzero(&data, sizeof(data));

	if (parser(&data, ac, av) != EXIT_SUCCESS)
		return (free_game(&data), EXIT_FAILURE);
	// mlx
	if (init_game(&data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	mlx_loop(data.mlx);
	//cleanup_game_mlx(&data); not shure here!!
	return (free_game(&data), EXIT_SUCCESS);
}

// TODO 
/*
- First make the map file *DONE
- the map file location should be the second argument of av so av[1] *DONE
- Then we have to make sure it's a valid file name *DONE
- Once the validation happens we have to read the file using getnextline *DONE
- after making the loop to read each line now we need to parse each line and see if we can identify the ONLY valid points of info we can get from the file which are a total of 7
- after identifying what part of info it is we have to save them to their respective points to be available for the rest of the project.
- 4 files: parser, parse color, parse texture, parse map.

*/

// testing for GNL
// static int test_file(char **av)
// {
// 	int	fd;
// 	char *line;

// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 		return (print_error(OPEN_FAILED), EXIT_FAILURE);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("[%s]\n", line);
// 		free (line);
// 		line = NULL;
// 	}
// 	close (fd);
// 	return (0);
// }
