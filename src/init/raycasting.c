/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:20:17 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/10 10:18:58 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// creates the ray for the current screen column
static void	init_ray(t_game *game, t_raycasting *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH -1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

// calculates direction and initial distances to grid boundaries
static void	calculate_step(t_game *game, t_raycasting *ray)
{
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	if (ray->step_x < 0)
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	if (ray->step_y < 0)
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
}

// travels through the map until it hits a wall
static void	perform_dda(t_game *game, t_raycasting *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(game, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

// calculates the walls distance and projected height
void	ray_casting(t_game *game)
{
	t_raycasting	ray;
	int				x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		calculate_step(game, &ray);
		perform_dda(game, &ray);
		calculate_wall(&ray);
		draw_wall(game, &ray, x);
		x++;
	}
}
