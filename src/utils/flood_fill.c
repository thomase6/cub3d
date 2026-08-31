/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 20:16:44 by texenber          #+#    #+#             */
/*   Updated: 2026/08/31 16:21:05 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fix_map(t_game *data)
{
	char *new_r;
	int	y;
	int space;
	
	y = 0;
	while (data->map.map_grid[y] != NULL)
	{
		if ((int)ft_strlen(data->map.map_grid[y]) < data->map.width)
		{
			new_r = malloc(sizeof(char) * (data->map.width + 1));
			if (!new_r)
				return (EXIT_FAILURE);
			ft_strlcpy(new_r, data->map.map_grid[y], data->map.width + 1);
			space = (int)ft_strlen(data->map.map_grid[y]);
			while (space < data->map.width)
			{
				new_r[space] = ' ';
				space++;
			}
			new_r[data->map.width] = '\0';
			free(data->map.map_grid[y]);
			data->map.map_grid[y] = new_r;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	**create_visited(t_game *data)
{
	int	**tmp;
	int	i;

	i = 0;
	tmp = malloc(sizeof(int *) * data->map.height);
	if (!tmp)
		return (NULL);
	while (i < data->map.height)
	{
		tmp[i] = malloc(sizeof(int) * data->map.width);
		if (!tmp[i])
			return (free_visited(tmp, i), NULL);
		ft_bzero(tmp[i], (sizeof(int) * data->map.width));
		i++;
	}
	return (tmp);
}

int	ft_flood_fill(t_game *data)
{
	int **visited;
	t_point	list[data->map.height * data->map.width];
	t_point current;
	int	top;
	
	top = -1;
	visited = create_visited(data);
	if (!visited)
		return (EXIT_FAILURE);
	top++;
	list[top].x = data->player.x;
	list[top].y = data->player.y;
	while (top != -1)
	{
		current = list[top];
		top--;
		if (current.y < 0 || current.y >= data->map.height || current.x < 0)
			return (free_visited(visited, data->map.height), 
					print_error(MAP_NOT_ENCLOSED), EXIT_FAILURE);
		if (current.x >= (int)ft_strlen(data->map.map_grid[current.y]))
			return (free_visited(visited, data->map.height),
					print_error(MAP_NOT_ENCLOSED), EXIT_FAILURE);
		if (data->map.map_grid[current.y][current.x] == ' ' 
			|| data->map.map_grid[current.y][current.x] == '\t')
			return (free_visited(visited, data->map.height),
					print_error(MAP_NOT_ENCLOSED), EXIT_FAILURE);
		if (visited[current.y][current.x] == 1)
			continue;
		else
			visited[current.y][current.x] = 1;
		if (data->map.map_grid[current.y][current.x] != '1')
		{
			top++;
			list[top].x = current.x;
			list[top].y = current.y - 1;
			top++;
			list[top].x = current.x;
			list[top].y = current.y + 1;
			top++;
			list[top].x = current.x - 1;
			list[top].y = current.y;
			top++;
			list[top].x = current.x + 1;
			list[top].y = current.y;
		}
	}
	free_visited(visited, data->map.height);
	return (EXIT_SUCCESS);
}
