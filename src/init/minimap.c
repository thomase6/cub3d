/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:19:59 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/06 14:51:34 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	helper_minimap(t_game *game, t_minimap *values)
{
	while (values->tile_y < values->size)
	{
		put_pixel(game, values->x * values->size + values->tile_x,
			values->y * values->size + values->tile_y, 0x00FFFFFF);
		values->tile_y++;
	}
}

void	draw_minimap(t_game *game)
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

void	draw_minimap_player(t_game *game)
{
	int	x;
	int	y;

	x = game->player.x * 8;
	y = game->player.y * 8;
	put_pixel(game, x, y, 0x00FF0000);
}

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 250)
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
	while (i < 36)
	{
		data.angle = data.start_angle + i * (data.fov / 35);
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
