/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:20:40 by stbagdah          #+#    #+#             */
/*   Updated: 2026/07/29 08:47:36 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.map_grid[y][x])
		{
			c = game->map.map_grid[y][x];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				if (c == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = 0.66;
				}
				else if (c == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = -0.66;
				}
				break ;
			}
			x++;
		}
		if (game->player.dir_x != 0 || game->player.dir_y != 0)
			break ;
		y++;
	}
	game->player.move_forward = 0;
	game->player.move_backward = 0;
	game->player.turn_left = 0;
	game->player.turn_right = 0;
}
/*
void	init_player(t_game *game)
{
	game->player.x = 5.5; // starting position 
	game->player.y = 5.5;
	game->player.dir_x = 0; // looking direction
	game->player.dir_y = 0; 
	
	if (game->player.start_dir == 'N')
	{	
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	if (game->player.start_dir == 'E')
	{	
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	if (game->player.start_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;	
	}
	if (game->player.start_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}	
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.move_forward = 0;  // not moving anywhere !
	game->player.move_backward = 0;
	game->player.turn_left = 0;
	game->player.turn_right = 0;
}
*/
