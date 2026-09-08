/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 09:53:55 by texenber          #+#    #+#             */
/*   Updated: 2026/09/08 15:57:47 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_game *data)
{
	int	x;
	int	y;
	int	p_count;

	y = 0;
	p_count = 0;
	if (data->map.height <= 0)
		return (print_error(MAP_FAIL), EXIT_FAILURE);
	while (data->map.map_grid[y])
	{
		x = 0;
		while(data->map.map_grid[y][x] != '\0')
		{
			if (data->map.map_grid[y][x] == 'N' || 
				data->map.map_grid[y][x] == 'S' || 
				data->map.map_grid[y][x] == 'E' || 
				data->map.map_grid[y][x] == 'W')
			{
				p_count += 1;
				data->player.x = x; // REMINDER: ADD 0.5 TO X AND Y AFTER VALIDATION OF EVERYTHING IS DONE
				data->player.y = y;
				data->player.p_dir = data->map.map_grid[y][x];
			}
			x++;
		}
		y++;
	}
	if (p_count < 1)
		return (print_error(NO_PLAYER), EXIT_FAILURE);
	if (p_count > 1)
		return (print_error(TOO_MANY_PLAYERS), EXIT_FAILURE);
	if (fix_map(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (ft_flood_fill(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int validate_all(t_game *data)
{
	if (data->map.north == NULL || data->map.south == NULL || 
		data->map.east == NULL || data->map.west == NULL || 
		data->map.has_ceiling == false || data->map.has_floor == false)
		return (print_error(MISS_CONFIG), EXIT_FAILURE);
	if (validate_map(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int process_line(t_game *data, char *line)
{
	char	*s;

	if ((s = ft_strrchr(line, '\n')) != 0)
		*s = '\0';
	if (line[0] == '\0')
	{
		if (data->map.map_started != 0)
			return (print_error(EMPTY_LINE_IN_MAP), EXIT_FAILURE);
		else
			return (EXIT_SUCCESS); 
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || 
		ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "WE ", 3) == 0)
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
	int i; //TESTING ONLY
	
	i = 0; //TESTING ONLY
	if (ac != 2)
		return (print_error(ARG_COUNT), EXIT_FAILURE);
	if (validate_arg(av) != EXIT_SUCCESS)
		return (print_error(INVALID_ARG), EXIT_FAILURE);
	if (read_file(data, av) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (validate_all(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (data->map.map_grid[i] != NULL) //TESTING ONLY
	{
		printf("[%s]\n", data->map.map_grid[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
