/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 13:21:06 by texenber          #+#    #+#             */
/*   Updated: 2026/11/14 18:51:12 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	store_grid_line(t_game *data, char *line)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (data->map.height + 2));
	if (tmp == NULL)
		return (EXIT_FAILURE);
	if (data->map.map_grid != NULL)
	{
		while (data->map.map_grid[i] != NULL)
		{
			tmp[i] = data->map.map_grid[i];
			i++;
		}
	}
	tmp[i] = ft_strdup(line);
	if (tmp[i] == NULL)
		return (free(tmp), EXIT_FAILURE);
	tmp[i + 1] = NULL;
	free(data->map.map_grid);
	data->map.map_grid = tmp;
	data->map.height += 1;
	if ((int)ft_strlen(line) > data->map.width)
		data->map.width = ft_strlen(line);
	return (EXIT_SUCCESS);
}

int	is_mapchar(char c)
{
	int		i;
	char	*s;

	s = " 10NSWE";
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
				return (print_error(INVAL_MAP_CHAR), EXIT_FAILURE);
		}
		data->map.map_started = 1;
		if (store_grid_line(data, line) != EXIT_SUCCESS)
			return (print_error(ALLOC_FAIL), EXIT_FAILURE);
	}
	else
		return (print_error(NOT_MAP_LINE), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
