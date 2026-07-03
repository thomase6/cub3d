/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:53:55 by texenber          #+#    #+#             */
/*   Updated: 2026/07/03 09:53:59 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// not implemented yet
// int validate_textures(char *arg)
// {
// 	int	len;
// 	char *tex_str;

// 	len = ft_strlen(arg);
// 	if (len < 4)
// 		return (EXIT_FAILURE);
// 	tex_str = ft_strrchr(arg, '.');
// 	if (tex_str == NULL)
// 		return (EXIT_FAILURE);
// 	if (ft_strcmp(tex_str, ".xmp") != 0)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

int	texture_extraction(char **target, char *line)
{
	int		i;
	char	*s;
	
	i = 2;
	if (*target != NULL)
		return(print_error(TEXT_DUP), EXIT_FAILURE);
	while (ft_is_space(line[i]) != 0)
		i++;
	if ((s = ft_strrchr(line, '\n')) != 0)
		*s = '\0';
	*target = ft_strdup(line + i);
	if (*target == NULL)
		return (print_error(STRDUP_FAIL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_textures(t_game *data, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{	
		if (texture_extraction(&data->map.north, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.north); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{	
		if (texture_extraction(&data->map.south, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.south); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{	
		if (texture_extraction(&data->map.east, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.east); // FOR TESTING ONLY
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{	
		if (texture_extraction(&data->map.west, line) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		printf("%s\n", data->map.west); // FOR TESTING ONLY
	}
	return(EXIT_SUCCESS);
}

int read_file(t_game *data, char **av)
{	
	int	fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILED), EXIT_FAILURE);
	while((line = get_next_line(fd)))
	{
		if (parse_textures(data, line) != EXIT_SUCCESS)
			return (get_next_line(-1), free(line), close(fd), EXIT_FAILURE);
		free(line);
	}
	get_next_line(-1);
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


// notes for read_file
// printf("%s", line); // managed to print a single line from the top of the file with this
// we need to parse each line to check what line type they are if they are a color line, a texture line or a map line.
// if the line starts with NO/SO/WE/EA
// 	. You must have exactly one of each: NO, SO, WE, EA.
// 	. The file path must point to a readable .xpm file.
// 	. No duplicate identifiers (e.g., two NO lines).
// 	. No invalid identifiers (e.g., NX, ZZ, or missing one).
// I think at this point we can atleast use 2 different functions to parse the lines with identifiers
// the issue will be identifying and parsing the map itself
// maybe if it fails the other 2 parses we can have a while loop over the lines until the end of file and grab the map grid from there.


// Old version 
// i = 2;
// while (ft_is_space(line[i]) != 0)
	// i++;
// if ((s = ft_strrchr(line, '\n')) != 0)
	// *s = '\0';
// if (data->map.north != NULL)
	// return(print_error(TEXT_DUP), EXIT_FAILURE);
// data->map.north = ft_strdup(line + i);
// printf("%s", data->map.north);