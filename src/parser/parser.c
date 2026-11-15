/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:53:55 by texenber          #+#    #+#             */
/*   Updated: 2026/11/15 10:49:03 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_line(t_game *data, char *line)
{
	char	*s;

	s = ft_strrchr(line, '\n');
	if (s)
		*s = '\0';
	if (line[0] == '\0')
	{
		if (data->map.map_started != 0)
			return (print_error(EMPTY_LINE_IN_MAP), EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0)
		return (parse_textures(data, line));
	else if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		return (parse_colors(data, line));
	else
		return (parse_map(data, line));
}

int	read_file(t_game *data, char **av)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(OPEN_FAILED), EXIT_FAILURE);
	if (read(fd, NULL, 0) == -1)
		return (print_error(FAIL_READ), close(fd), EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(data, line) != EXIT_SUCCESS)
			return (get_next_line(-1), free(line), close(fd), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-1);
	return (close(fd), EXIT_SUCCESS);
}

int	validate_arg(char **av)
{
	int		len;
	char	*cub_str;

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
	if (validate_all(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
