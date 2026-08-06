/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:19:59 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/03 14:37:13 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	helper_minimap(t_game *game, t_minimap *values) // old version
{
	while (values->tile_y < values->size)
	{
		put_pixel(game, values->x * values->size + values->tile_x,
			values->y * values->size + values->tile_y, 0x00FFFFFF);
		values->tile_y++;
	}
}

static void	draw_tile(t_game *game, int minimap_x, int minimap_y)
{
	int	x;
	int	y;
	
	x = 0;
	while (x < MINI_TILE)
	{
		y = 0;
		while (y < MINI_TILE)
		{
			put_pixel(game, minimap_x + x, minimap_y + y; 0x00FFFFFF);
			y++;
		}
		x++;
	} 
}

void	draw_minimap(t_game *game) // add to .h !!
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	start_x = (int)game->player.x - 16;
	start_y = (int)game->player.y - 6;

	end_x = (int)game->player.x + 16;
	end_y = (int)game->player.y + 6;

	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		while (x <= end_x)
		{
			if (game->map.grid[y][x] == '1')
				draw_minimap_tile(game, x, y);
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
void	draw_minimap(t_game *game) // old version
{
	t_minimap	values;

	values.size = 8;
	values.y = 0;
	while (game->map.grid[values.y])
	{
		values.x = 0;
		while (game->map.grid[values.y][values.x])
		{
			if (game->map.grid[values.y][values.x] == '1')
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

void	draw_minimap_tile(t_game *game, int map_x, int map_y) // uses t_minimap struct maybe?
{
	float	wall_x;
	float	wall_y;
	int	minimap_x;
	int	minimap_y;
	
	wall_x = MINI_CENTER_X + ((map_x - game->player.x) * MINI_TILE);
	wall_y = MINI_CENTER_Y + ((map_y - game->player.y) * MINI_TILE);
	minimap_x = (int)wall_x;
	minimap_y = (int)wall_y;
	draw_tile(game, minimap_x, minimap_y);
}

void	draw_minimap_player(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x * MINI_TILE;
	y = game->player.y * MINI_TILE;
	put_pixel(game, x, y, 0x00FF0000);
}

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
			put_pixel(game, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

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
			put_pixel(game, (int)(data.ray_x * data.scale),
				(int)(data.ray_y * data.scale), 0x00FFFF00);
		}
		i++;
	}
}
