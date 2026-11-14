/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:41:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/14 17:27:35 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	main(int ac, char **av)
{
	t_game		data;

	if (ac != 2)
		return (print_error(ARG_COUNT), EXIT_FAILURE);
	ft_bzero(&data, sizeof(data));
	if (parser(&data, ac, av) != EXIT_SUCCESS)
		return (free_game(&data), EXIT_FAILURE);
	if (init_game(&data) != EXIT_SUCCESS)
		return (free_game(&data), EXIT_FAILURE);
	mlx_loop(data.mlx);
	return (free_game(&data), EXIT_SUCCESS);
}
