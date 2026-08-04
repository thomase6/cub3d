/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:42:28 by stbagdah          #+#    #+#             */
/*   Updated: 2026/07/29 08:51:21 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->player.move_forward = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		game->player.move_backward = 1;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player.turn_left = 1;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player.turn_right = 1;
	if (keycode == ESC)
		close_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->player.move_forward = 0;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		game->player.move_backward = 0;
	if (keycode == KEY_A || keycode == KEY_LEFT)
		game->player.turn_left = 0;
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		game->player.turn_right = 0;
	return (0);
}
