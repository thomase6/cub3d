/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:53:55 by texenber          #+#    #+#             */
/*   Updated: 2026/06/26 10:22:03 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int read_file(t_game **data, char **av)
{	
	int	fd; //this needs to be map->fd
	char *line;
	
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILED), EXIT_FAILURE);
	while((line = get_next_line(fd)) != NULL) // all that is needed is to have this line to save the result from gnl to a variable.
		printf("%s", line); // managed to print a single line from the top of the file with this
	// after opening the file we need to be able to go through each line one at a time.
	// we need to parse each line to check what line type they are if they are a color line, a texture line or a map line.
	// then check the possible characters that can be used per line type ex. map can only contain 1/0/N/W/E/S/' '.
	return (EXIT_SUCCESS);
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
	if (read_file(&data, av) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}