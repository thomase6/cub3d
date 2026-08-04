/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:20:17 by stbagdah          #+#    #+#             */
/*   Updated: 2026/07/29 08:52:01 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_raycasting *ray, int x)
{
	ray->cameraX = 2 * x / (double)WIN_WIDTH -1;
	ray->rayDirX = game->player.dir_x + game->player.plane_x * ray->cameraX;
	ray->rayDirY = game->player.dir_y + game->player.plane_y * ray->cameraX;
	ray->mapX = (int)game->player.x;
	ray->mapY = (int)game->player.y;
	ray->deltaDistX = fabs(1.0 / ray->rayDirX);
	ray->deltaDistY = fabs(1.0 / ray->rayDirY);
}

static void	calculate_step(t_game *game, t_raycasting *ray)
{
	if (ray->rayDirX < 0)
		ray->stepX = -1;
	else
		ray->stepX = 1;// can me put this together ? i think so :)
	if (ray->rayDirY < 0)
		ray->stepY = -1;
	else
		ray->stepY = 1;
	if (ray->stepX < 0)
		ray->sideDistX = (game->player.x - ray->mapX) * ray->deltaDistX;
	else
		ray->sideDistX = (ray->mapX + 1.0 - game->player.x) * ray->deltaDistX;
	if (ray->stepY < 0)
		ray->sideDistY = (game->player.y - ray->mapY) * ray->deltaDistY;
	else
		ray->sideDistY = (ray->mapY + 1.0 - game->player.y) * ray->deltaDistY;
}

static void	perform_dda(t_game *game, t_raycasting *ray)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (is_wall(game, ray->mapX, ray->mapY))
			ray->hit = 1;
	}
}

static void	calculate_wall(t_raycasting *ray)
{
	if (!ray->side)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
	ray->drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT -1;
}

static void	draw_wall(t_game *game, t_raycasting *ray, int x)
{
	int	y;

	y = ray->drawStart;
	while (y < ray->drawEnd)
	{
		put_pixel(game, x, y, 0x00FFFFFF);
		y++;
	}
}

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
/*
void	ray_casting(t_game *game)
{
	int		x;
	int		y;
	t_raycasting	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray.cameraX = 2 * x / (double)WIN_WIDTH -1;
		ray.rayDirX = game->player.dir_x + game->player.plane_x * ray.cameraX;
		ray.rayDirY = game->player.dir_y + game->player.plane_y * ray.cameraX;
		ray.mapX = (int)game->player.x;
		ray.mapY = (int)game->player.y;
		ray.deltaDistX = fabs(1 / ray.rayDirX);
		ray.deltaDistY = fabs(1 / ray.rayDirY);
		if (ray.rayDirX < 0)
			ray.stepX = -1;
		else
			ray.stepX = 1;     // can me put this together ? i think so :)
		if (ray.rayDirY < 0)
			ray.stepY = -1;
		else
			ray.stepY = 1;
		if (ray.stepX < 0)
			ray.sideDistX = (game->player.x - ray.mapX) * ray.deltaDistX;
		else
			 ray.sideDistX = (ray.mapX + 1.0 - game->player.x) * ray.deltaDistX;
		if (ray.stepY < 0)
			ray.sideDistY = (game->player.y - ray.mapY) * ray.deltaDistY;
		else
			ray.sideDistY = (ray.mapY + 1.0 -game->player.y) * ray.deltaDistY;
		ray.hit = 0;
		while (!ray.hit)
		{
			if (ray.sideDistX < ray.sideDistY)
			{
				ray.sideDistX += ray.deltaDistX;
				ray.mapX += ray.stepX;
				ray.side = 0;
			}
			else
			{
				ray.sideDistY += ray.deltaDistY;
				ray.mapY += ray.stepY;
				ray.side = 1;
			}
			if (is_wall(game, ray.mapX, ray.mapY))
				ray.hit = 1;	
		}
		if (!ray.side)
			ray.perpWallDist = ray.sideDistX - ray.deltaDistX;
		else
			ray.perpWallDist = ray.sideDistY - ray.deltaDistY;
		ray.lineHeight = (int)(WIN_HEIGHT / ray.perpWallDist);
		ray.drawStart = - ray.lineHeight / 2 + WIN_HEIGHT / 2;
		ray.drawEnd = ray.lineHeight / 2 + WIN_HEIGHT / 2;
		if (ray.drawStart < 0)
			ray.drawStart = 0;
		if (ray.drawEnd >= WIN_HEIGHT)
			ray.drawEnd = WIN_HEIGHT -1;
		y = ray.drawStart;
		while (y < ray.drawEnd)
		{
			put_pixel(game, x , y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}
*/
