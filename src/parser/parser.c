/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:53:55 by texenber          #+#    #+#             */
/*   Updated: 2026/08/04 18:17:30 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int process_line(t_game *data, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0)
	{
		if (parse_textures(data, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
	{
		if (parse_colors(data, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else 
	{
		if (parse_map(data, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int read_file(t_game *data, char **av)
{	
	int	fd;
	char *line;
	int i; //TESTING ONLY
	
	i = 0; //TESTING ONLY
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILED), EXIT_FAILURE);
	while((line = get_next_line(fd)))
	{
		if (process_line(data, line) != EXIT_SUCCESS)
			return (get_next_line(-1), free(line), close(fd), EXIT_FAILURE);
		free(line);
	}
	get_next_line(-1);
	while (data->map.map_grid[i] != NULL) //TESTING ONLY
	{
		printf("[%s]\n", data->map.map_grid[i]);
		i++;
	}
	return (close(fd), EXIT_SUCCESS);
}

int	validate_arg(char **av)
{
	int	len;
	char *cub_str;

	len = ft_strlen(av[1]);
	if (len < 4)
		return (EXIT_FAILURE);
	cub_str = ft_strrchr(av[1], '.');
	if (cub_str == NULL)
		return (EXIT_FAILURE);
	if (ft_strcmp(cub_str, ".cub") != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parser(t_game *data, int ac, char **av)
{

	if (ac != 2)
		return (print_error(ARG_COUNT), EXIT_FAILURE);
	if (validate_arg(av) != EXIT_SUCCESS)
		return (print_error(INVALID_ARG), EXIT_FAILURE);
	if (read_file(data, av) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// after reading the whole file we need to make sure that we have all the pieces of information, the map, the ceiling color, the floor color and the 4 texture colors. If we don't we should just print out an error.
// the issue will be identifying and parsing the map itself
// maybe if it fails the other 2 parses we can have a while loop over the lines until the end of file and grab the map grid from there.


		// if blank skip the line
		// wrong input has to be taken into account and print an error 
		// if map line, parse the map
