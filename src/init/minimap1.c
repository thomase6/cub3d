/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 10:20:52 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/10 11:01:02 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_player(t_game *game)
{
	put_pixel(game, MINI_CENTER_X, MINI_CENTER_Y, 0x00FFFFFF);
}

void	draw_minimap_floor(t_game *game, int map_x, int map_y)
{
	int	minimap_x;
	int	minimap_y;

	minimap_x = MINI_CENTER_X
		+ (int)((map_x - game->player.x) * MINI_TILE);
	minimap_y = MINI_CENTER_Y
		+ (int)((map_y - game->player.y) * MINI_TILE);
	draw_tile(game, minimap_x, minimap_y, 0x00AAAAAA);
}

static void	get_minimap_bounds(t_game *game, int *bounds)
{
	bounds[0] = (int)game->player.x - (MINI_CENTER_X / MINI_TILE) - 1;
	bounds[1] = (int)game->player.y - (MINI_CENTER_Y / MINI_TILE) - 1;
	bounds[2] = (int)game->player.x + (MINI_CENTER_X / MINI_TILE) + 1;
	bounds[3] = (int)game->player.y + (MINI_CENTER_Y / MINI_TILE) + 1;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[1] < 0)
		bounds[1] = 0;
	if (bounds[2] > game->map.width)
		bounds[2] = game->map.width;
	if (bounds[3] > game->map.height)
		bounds[3] = game->map.height;
}

static void	draw_minimap_row(t_game *game, int y, int start_x, int end_x)
{
	int	x;

	x = start_x;
	while (x < end_x && x < (int)ft_strlen(game->map.map_grid[y]))
	{
		if (game->map.map_grid[y][x] == '1')
			draw_minimap_tile(game, x, y);
		else if (game->map.map_grid[y][x] == '0'
			|| game->map.map_grid[y][x] == 'N'
			|| game->map.map_grid[y][x] == 'S'
			|| game->map.map_grid[y][x] == 'E'
			|| game->map.map_grid[y][x] == 'W')
			draw_minimap_floor(game, x, y);
		x++;
	}
}

void	draw_minimap(t_game *game)
{
	int	bounds[4];
	int	y;

	get_minimap_bounds(game, bounds);
	y = bounds[1];
	while (y < bounds[3])
	{
		draw_minimap_row(game, y, bounds[0], bounds[2]);
		y++;
	}
}
