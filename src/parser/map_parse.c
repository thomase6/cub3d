/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 13:21:06 by texenber          #+#    #+#             */
/*   Updated: 2026/07/28 10:59:08 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	store_grid_and_player(t_game *data, char *line)
{
	char **tmp;
	int	i;

	i = 0;
	tmp = malloc(sizeof(char *) * (data->map.map_height + 2));
	if (tmp == NULL)
		return (EXIT_FAILURE);
	if (data->map.map_grid != NULL)
	{
		while (data->map.map_grid[i] != NULL)
		{
			tmp[i] = data->map.map_grid[i];
			if (tmp[i] == NULL)
			{
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	data->map.map_height += 1;
	return (EXIT_SUCCESS);
}

int	is_mapchar(char c)
{
	int	i;
	char *s = " \t10NSWE";

	i = 0;
	while (s[i] != '\0')
	{
		if (c == s[i])
			return (1); 
		i++;
	}
	return (0);
}

int	parse_map(t_game *data, char *line)
{
	int	i;
	char *t;

	if ((t = ft_strrchr(line, '\n')) != 0)
		*t = '\0';
	i = 0;
	if (line[0] == '\0')
	{
		if (data->map.map_started != 0)
			return (print_error(EMPTY_LINE_IN_MAP), EXIT_FAILURE);
		else
			return (EXIT_SUCCESS); 
	}

	if (is_mapchar(line[0]) != 0)
	{
		while (line[i])
		{
			if (is_mapchar(line[i]) != 0)
				i++;
			else
				return (print_error(INVAL_MAP_CHAR), EXIT_FAILURE);
		}
		data->map.map_started = 1;
		store_grid_and_player_direction(data, line);	
	}
	else
	{
		if (data->map.map_started != 0)
			return (print_error(NOT_MAP_LINE), EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
	// TODO:
		// figure out how to implement the flag once the map has started to be parsed.
		// once the flag is set if an empty line or line that is not a map line is found we should print an error because of invalid map.
}

	// include:
		// this is specifically the characters ' ', 1, 0, N/W/E/S
		// reading a line with exclusively this characters means that we are reading the map 
		// once we detect a map line we need to set a flag that the map has been detected
		// if the map is detected all lines from then on should be the map.
		// the map is the last piece of data that is found in the .cub file.
		// this means that we shouldn't have any other data in between or after the map.
			// if anything else is found then we need to send out an error.
	// "if line is not ' ', 1, 0, N/S/E/W && the map flag is on we need to print out an error."
		// both checks happen in the same line as they are both critical to make sure that this is always true for every line.
		// maybe we can compare the string to a strnstr with all the characters that are whitelisted and the moment one is not detected we print the error.	


// if line is blank:
// 		if map_started
			// error;
// 		else
			// ignore, return success
			
// if line is valid map line (all chars pass is_mapchar):
// 		set map_started = true
// 		store line in map_grid
// 		return success
// else
//     return error