/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 12:06:09 by texenber          #+#    #+#             */
/*   Updated: 2026/11/14 16:58:22 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	push_y(int **visited, t_point *list, int *top, t_point current)
{
	if (visited[current.y - 1][current.x] != 1)
	{
		visited[current.y - 1][current.x] = 1;
		(*top)++;
		list[*top].x = current.x;
		list[*top].y = current.y - 1;
	}
	if (visited[current.y + 1][current.x] != 1)
	{
		visited[current.y + 1][current.x] = 1;
		(*top)++;
		list[*top].x = current.x;
		list[*top].y = current.y + 1;
	}
}

void	push_x(int **visited, t_point *list, int *top, t_point current)
{
	if (visited[current.y][current.x - 1] != 1)
	{
		visited[current.y][current.x - 1] = 1;
		(*top)++;
		list[*top].x = current.x - 1;
		list[*top].y = current.y;
	}
	if (visited[current.y][current.x + 1] != 1)
	{
		visited[current.y][current.x + 1] = 1;
		(*top)++;
		list[*top].x = current.x + 1;
		list[*top].y = current.y;
	}
}

void	init_list_and_visited(int **visited, t_point *list,
		int *top, t_game *data)
{
	*top = 0;
	list[*top].x = data->player.x;
	list[*top].y = data->player.y;
	visited[(int)data->player.y][(int)data->player.x] = 1;
}
