/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:30:25 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/06 14:52:29 by texenber         ###   ########.fr       */
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
	if (map_x >= (int)ft_strlen(game->map.map_grid[map_y])) // needed for not pefect rectangles map
		return (1);
	if (game->map.map_grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	//free(game->mlx);
	exit(0);
	return (0);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 800 || y >= 600) // so we can use global vairable !!
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}
