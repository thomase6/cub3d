/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 10:41:27 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/09 10:41:38 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*pick_texture(t_game *game, t_raycasting *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->tex[EA]);
		return (&game->tex[WE]);
	}
	if (ray->ray_dir_y > 0)
		return (&game->tex[SO]);
	return (&game->tex[NO]);
}

void	draw_wall(t_game *game, t_raycasting *ray, int x)
{
	t_img	*tex;
	double	wall_x;
	double	tex_pos;
	int		tex_x;
	int		y;

	tex = pick_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* ((double)tex->height / ray->line_height);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(game, x, y, get_tex_color(tex, tex_x, (int)tex_pos));
		tex_pos += (double)tex->height / ray->line_height;
		y++;
	}
}

void	calculate_wall(t_raycasting *ray)
{
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT -1;
}
