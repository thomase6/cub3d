/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:19:59 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/10 11:06:12 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_game *game, int minimap_x, int minimap_y, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINI_TILE + 1)
	{
		y = 0;
		while (y < MINI_TILE + 1)
		{
			if (minimap_x + x >= 0 && minimap_x + x < (MINI_CENTER_X * 2)
				&& minimap_y + y >= 0 && minimap_y + y < (MINI_CENTER_Y * 2))
				put_pixel(game, minimap_x + x, minimap_y + y, color);
			y++;
		}
		x++;
	}
}

void	draw_minimap_tile(t_game *game, int map_x, int map_y)
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

static void	init_mini_ray(t_game *game, t_mini_ray *data, int i)
{
	data->angle = data->start_angle + i * (data->fov / (MINI_MAP_RAYS - 1));
	data->ray_dir_x = cos(data->angle);
	data->ray_dir_y = sin(data->angle);
	data->ray_x = game->player.x;
	data->ray_y = game->player.y;
}

static void	draw_single_ray(t_game *game, t_mini_ray *data)
{
	while (!is_wall(game, data->ray_x, data->ray_y))
	{
		data->ray_x += data->ray_dir_x * data->step;
		data->ray_y += data->ray_dir_y * data->step;
		put_pixel(game, MINI_CENTER_X + (data->ray_x - game->player.x)
			* MINI_TILE, MINI_CENTER_Y + (data->ray_y - game->player.y)
			* MINI_TILE, 0x00FFFF00);
	}
}

void	draw_minimap_rays(t_game *game)
{
	int			i;
	t_mini_ray	data;

	i = 0;
	data.step = 0.02;
	data.fov = 66 * M_PI / 180;
	data.start_angle = atan2(game->player.dir_y, game->player.dir_x)
		- data.fov / 2;
	while (i < MINI_MAP_RAYS)
	{
		init_mini_ray(game, &data, i);
		draw_single_ray(game, &data);
		i++;
	}
}
