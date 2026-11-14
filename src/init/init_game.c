/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:32:22 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/19 12:34:47 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update(t_game *game)
{
	t_next_position	movement;

	clear_image(game);
	movement.next_x = game->player.x;
	movement.next_y = game->player.y;
	if (game->player.turn_left)
		rotate_player(game, -ROT_SPEED);
	if (game->player.turn_right)
		rotate_player(game, ROT_SPEED);
	if (game->player.move_forward)
		move_player(game, &movement, 0, SPEED);
	if (game->player.move_backward)
		move_player(game, &movement, 1, SPEED);
	if (game->player.move_left)
		move_player(game, &movement, 2, SPEED);
	if (game->player.move_right)
		move_player(game, &movement, 3, SPEED);
	collision_check(game, &movement, RADIUS);
	render_game(game);
	display_frame(game);
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (load_textures(game) != EXIT_SUCCESS)
	{
		free_textures(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (EXIT_FAILURE);
	}
	if (!game->mlx)
		return (EXIT_FAILURE);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		return ((free(game->mlx)), EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_len,
			&game->endian);
	init_player(game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		game->player.move_forward = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		game->player.move_backward = 1;
	if (keycode == KEY_A)
		game->player.move_left = 1;
	if (keycode == KEY_D)
		game->player.move_right = 1;
	if (keycode == KEY_LEFT)
		game->player.turn_left = 1;
	if (keycode == KEY_RIGHT)
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
	if (keycode == KEY_A)
		game->player.move_left = 0;
	if (keycode == KEY_D)
		game->player.move_right = 0;
	if (keycode == KEY_LEFT)
		game->player.turn_left = 0;
	if (keycode == KEY_RIGHT)
		game->player.turn_right = 0;
	return (0);
}
