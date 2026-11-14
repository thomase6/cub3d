/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 20:16:44 by texenber          #+#    #+#             */
/*   Updated: 2026/11/14 17:04:59 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_cell(t_game *data, t_point current)
{
	if (data->map.map_grid[current.y][current.x] == ' ')
		return (1);
	if (data->map.map_grid[current.y][current.x] == '1')
		return (2);
	if (current.x == 0 || current.x == data->map.width - 1
		|| current.y == 0 || current.y == data->map.height - 1)
		return (1);
	return (0);
}

void	push_neighbors(int **visited, t_point *list, int *top, t_point current)
{
	push_y(visited, list, top, current);
	push_x(visited, list, top, current);
}

int	ft_flood_fill(t_game *data)
{
	int		**visited;
	t_point	*list;
	t_point	current;
	int		top;
	int		res;

	visited = create_visited(data);
	list = malloc(sizeof(t_point) * (data->map.height * data->map.width));
	if (!list || !visited)
		return (free_flood(visited, list, data->map.height),
			print_error(ALLOC_FAIL), EXIT_FAILURE);
	init_list_and_visited(visited, list, &top, data);
	while (top != -1)
	{
		current = list[top--];
		res = check_cell(data, current);
		if (res == 1)
			return (free_flood(visited, list, data->map.height),
				print_error(MAP_NOT_ENCLOSED), EXIT_FAILURE);
		else if (res == 2)
			continue ;
		push_neighbors(visited, list, &top, current);
	}
	free_flood(visited, list, data->map.height);
	return (EXIT_SUCCESS);
}
