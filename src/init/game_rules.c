/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:30:25 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/19 12:26:52 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (1);
	if (!game->map.map_grid[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(game->map.map_grid[map_y]))
		return (1);
	if (game->map.map_grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	close_game(t_game *game)
{
	free_textures(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	exit(0);
	return (0);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_img *tex, int x, int y)
{
	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	return (*(unsigned int *)(tex->addr + y * tex->line_len
			+ x * (tex->bpp / 8)));
}
