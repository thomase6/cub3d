/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 13:21:06 by texenber          #+#    #+#             */
/*   Updated: 2026/07/17 11:52:32 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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

	i = 0;
	if (is_mapchar(line[0]) != 0)
	{
		while (line[i])
		{
			if (is_mapchar(line[i]) != 0)
				i++;
			else
				return (EXIT_FAILURE);
		}
	}
	// return (EXIT_SUCCESS);
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