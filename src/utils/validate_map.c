/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:05:42 by texenber          #+#    #+#             */
/*   Updated: 2026/11/14 18:17:58 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fix_map(t_game *data)
{
	char	*new_r;
	int		y;
	int		space;

	y = 0;
	while (data->map.map_grid[y] != NULL)
	{
		if ((int)ft_strlen(data->map.map_grid[y]) < data->map.width)
		{
			new_r = malloc(sizeof(char) * (data->map.width + 1));
			if (!new_r)
				return (print_error(ALLOC_FAIL), EXIT_FAILURE);
			ft_strlcpy(new_r, data->map.map_grid[y], data->map.width + 1);
			space = (int)ft_strlen(data->map.map_grid[y]);
			while (space < data->map.width)
				new_r[space++] = ' ';
			new_r[data->map.width] = '\0';
			free(data->map.map_grid[y]);
			data->map.map_grid[y] = new_r;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	look_for_player(t_game *data, int y)
{
	int	x;
	int	p_count;

	p_count = 0;
	while (data->map.map_grid[y])
	{
		x = 0;
		while (data->map.map_grid[y][x] != '\0')
		{
			if (data->map.map_grid[y][x] == 'N'
				|| data->map.map_grid[y][x] == 'S'
				|| data->map.map_grid[y][x] == 'E'
				|| data->map.map_grid[y][x] == 'W')
			{
				p_count += 1;
				data->player.x = x;
				data->player.y = y;
				data->player.p_dir = data->map.map_grid[y][x];
			}
			x++;
		}
		y++;
	}
	return (p_count);
}

int	validate_map(t_game *data)
{
	int	y;
	int	p_count;

	y = 0;
	p_count = 0;
	if (data->map.height <= 0)
		return (print_error(MAP_FAIL), EXIT_FAILURE);
	p_count = look_for_player(data, y);
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

int	validate_all(t_game *data)
{
	if (data->map.north == NULL || data->map.south == NULL
		|| data->map.east == NULL || data->map.west == NULL
		|| data->map.has_ceiling == false || data->map.has_floor == false)
		return (print_error(MISS_CONFIG), EXIT_FAILURE);
	if (validate_map(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
