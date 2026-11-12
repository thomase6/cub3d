/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:51:25 by stbagdah          #+#    #+#             */
/*   Updated: 2026/07/27 12:10:34 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	move_player(t_game *game, t_next_position *movement,
					int direction, float speed)
{
	if (direction == 0)
	{
		movement->next_x += game->player.dir_x * speed;
		movement->next_y += game->player.dir_y * speed;
	}
	else if (direction == 1)
	{
		movement->next_x -= game->player.dir_x * speed;
		movement->next_y -= game->player.dir_y * speed;
	}
	else if (direction == 2)
	{
		movement->next_x += game->player.dir_y * speed;
		movement->next_y -= game->player.dir_x * speed;
	}
	else if (direction == 3)
	{
		movement->next_x -= game->player.dir_y * speed;
		movement->next_y += game->player.dir_x * speed;
	}
}
