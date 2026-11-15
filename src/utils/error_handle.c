/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:44:41 by texenber          #+#    #+#             */
/*   Updated: 2026/11/15 11:41:18 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

void	free_flood(int **visited, t_point *list, int height)
{
	if (visited != NULL)
		free_visited(visited, height);
	free (list);
}

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 1);
}

void	free_game(t_game *data)
{
	if (data->map.north != NULL)
		free(data->map.north);
	if (data->map.south != NULL)
		free(data->map.south);
	if (data->map.east != NULL)
		free(data->map.east);
	if (data->map.west != NULL)
		free(data->map.west);
	if (data->map.map_grid != NULL)
		free_arr(data->map.map_grid);
}
