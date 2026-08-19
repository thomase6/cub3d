/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:19:59 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/19 12:44:31 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
static void	helper_minimap(t_game *game, t_minimap *values) // old version
{
	while (values->tile_y < values->size)
	{
		put_pixel(game, values->x * values->size + values->tile_x,
			values->y * values->size + values->tile_y, 0x00FFFFFF);
		values->tile_y++;
	}
}
*/

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < (MINI_CENTER_Y * 2))
	{
		x = 0;
		while (x < (MINI_CENTER_X * 2))
		{
			put_pixel(game, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_game *game, int minimap_x, int minimap_y, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINI_TILE)
	{
		y = 0;
		while (y < MINI_TILE)
		{
			if (minimap_x + x >= 0 && minimap_x + x < (MINI_CENTER_X * 2)
				&& minimap_y + y >= 0 && minimap_y + y < (MINI_CENTER_Y * 2))
				put_pixel(game, minimap_x + x, minimap_y + y, color);
			y++;
		}
		x++;
	}
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

void	draw_minimap(t_game *game)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	start_x = (int)game->player.x - (MINI_CENTER_X / MINI_TILE) - 1;
	start_y = (int)game->player.y - (MINI_CENTER_Y / MINI_TILE) - 1;
	end_x = (int)game->player.x + (MINI_CENTER_X / MINI_TILE) + 1;
	end_y = (int)game->player.y + (MINI_CENTER_Y / MINI_TILE) + 1;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (end_x > game->map.width)
		end_x = game->map.width;
	if (end_y > game->map.height)
		end_y = game->map.height;
	y = start_y;
	while (y < end_y)
	{
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
		y++;
	}
}
/*
visible_tiles_x = minimap_width / tile_size
half_visible_x = visible_tiles_x / 2

visible_tiles_y = minimap_height / tile_size
half_visible_y = visible_tiles_y / 2
*/
/*
void	draw_minimap(t_game *game) // old version
{
	t_minimap	values;

	values.size = 8;
	values.y = 0;
	while (game->map.map_grid[values.y])
	{
		values.x = 0;
		while (game->map.map_grid[values.y][values.x])
		{
			if (game->map.map_grid[values.y][values.x] == '1')
			{
				values.tile_x = 0;
				while (values.tile_x < values.size)
				{
					values.tile_y = 0;
					helper_minimap(game, &values);
					values.tile_x++;
				}
			}
			values.x++;
		}
		values.y++;
	}
}
*/

void	draw_minimap_tile(t_game *game, int map_x, int map_y) // uses t_minimap struct maybe?
{
	float	wall_x;
	float	wall_y;
	int		minimap_x;
	int		minimap_y;

	wall_x = MINI_CENTER_X + ((map_x - game->player.x) * MINI_TILE);
	wall_y = MINI_CENTER_Y + ((map_y - game->player.y) * MINI_TILE);
	minimap_x = (int)wall_x;
	minimap_y = (int)wall_y;
	draw_tile(game, minimap_x, minimap_y, 0x00FFFFFF);
}

void	draw_minimap_player(t_game *game)
{
	put_pixel(game, MINI_CENTER_X, MINI_CENTER_Y, 0x00FFFFFF);
}

//(int)(data.ray_x * data.scale),
//(int)(data.ray_y * data.scale), 0x00FFFF00);
void	draw_minimap_rays(t_game *game)
{
	int			i;
	t_mini_ray	data;

	i = 0;
	data.scale = 8;
	data.step = 0.02;
	data.fov = 66 * M_PI / 180;
	data.start_angle = atan2(game->player.dir_y,
			game->player.dir_x) - data.fov / 2;
	while (i < MINI_MAP_RAYS)
	{
		data.angle = data.start_angle + i * (data.fov / (MINI_MAP_RAYS - 1));
		data.ray_dir_x = cos(data.angle);
		data.ray_dir_y = sin(data.angle);
		data.ray_x = game->player.x;
		data.ray_y = game->player.y;
		while (!is_wall(game, data.ray_x, data.ray_y))
		{
			data.ray_x += data.ray_dir_x * data.step;
			data.ray_y += data.ray_dir_y * data.step;
			put_pixel(game, MINI_CENTER_X + (data.ray_x - game->player.x) * MINI_TILE,
				MINI_CENTER_Y + (data.ray_y - game->player.y) * MINI_TILE, 0x00FFFF00);
		}
		i++;
	}
}
