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
	game->player.x = 1.5; // starting position 
	game->player.y = 1.5;
	game->player.dir_x = 1.0; // looking direction
	game->player.dir_y = 0.0; // x = 1 right x  -1 left y = 1 down y = -1 up
								// N = y = -1, O = x = 1, S = y = 1 ,W = x = -1;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.move_forward = 0;  // not moving anywhere !
	game->player.move_backward = 0;
	game->player.turn_left = 0;
	game->player.turn_right = 0;
}
