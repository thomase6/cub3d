/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:41:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/15 11:41:08 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		data;

	ft_bzero(&data, sizeof(data));
	if (parser(&data, ac, av) != EXIT_SUCCESS)
		return (free_game(&data), EXIT_FAILURE);
	if (init_game(&data) != EXIT_SUCCESS)
		return (free_game(&data), EXIT_FAILURE);
	mlx_loop(data.mlx);
	return (free_game(&data), EXIT_SUCCESS);
}
