/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 10:54:11 by stbagdah          #+#    #+#             */
/*   Updated: 2026/07/27 12:07:45 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(t_game *game)
{
	int	size;

	size = WIN_WIDTH * WIN_HEIGHT * (game->bpp / 8);
	ft_memset(game->addr, 0, size);
}

void	collision_check(t_game *game, t_next_position *movement, float radius)
{
	if (!is_wall(game, movement->next_x + radius, game->player.y)
		&& !is_wall(game, movement->next_x - radius, game->player.y))
		game->player.x = movement->next_x;
	if (!is_wall(game, game->player.x, movement->next_y + radius)
		&& !is_wall(game, game->player.x, movement->next_y - radius))
		game->player.y = movement->next_y;
}

void	render_game(t_game *game)
{
	ray_casting(game);
	draw_minimap_background(game);
	draw_minimap(game);
	draw_minimap_rays(game);
	draw_minimap_player(game);
}

void	display_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
