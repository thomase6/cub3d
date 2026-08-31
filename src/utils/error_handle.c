/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:44:41 by texenber          #+#    #+#             */
/*   Updated: 2026/08/24 20:48:02 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_visited(int **visited, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		if(visited[i] != NULL)
			free(visited[i]);
		i++;
	}
	free(visited);
}

void	print_error(char *msg)
{
	ft_putstr_fd(msg, 1);
}