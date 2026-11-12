/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:05:37 by stbagdah          #+#    #+#             */
/*   Updated: 2026/11/09 12:51:28 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_direction(t_game *game, char c)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	if (c == 'N' || c == 'S')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
		if (c == 'S')
		{
			game->player.dir_y = 1;
			game->player.plane_x = -0.66;
		}
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
	else if (c == 'E')
		game->player.dir_x = 1;
}

static void	set_player(t_game *game, int x, int y, char c)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	init_direction(game, c);
}

static int	find_player(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.map_grid[y][x])
		{
			c = game->map.map_grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player(game, x, y, c);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static void	init_controls(t_player *player)
{
	player->move_forward = 0;
	player->move_backward = 0;
	player->turn_left = 0;
	player->turn_right = 0;
}

void	init_player(t_game *game)
{
	if (!find_player(game))
		return ;
	init_controls(&game->player);
}

/*
Whole chain:raycasting pipline
screen column
      |
      v
cameraX (-1 to +1)
      |
      v
cameraPlane
      |
      v
rayDir
      |
      v
DDA
      |
      v
wall distance
      |
      v
wall height
      |
      v
pixel column

---------------------------------------------------------

playerDir
=
where the player looks

cameraPlane * cameraX
=
how far left/right we move from that view

----------------------------------------------------------

cameraX = -1 + 2 * x / screenWidth; // for each colum

rayDirX = playerDirX + planeX * cameraX; //
rayDirY = playerDirY + planeY * cameraX;


---------------------------------------------------------------------
x = 0;
while (x < SCREEN_WIDTH)
{
    // 1. Calculate cameraX

    // 2. Calculate rayDir

    // 3. Initialize DDA

    // 4. Run DDA

    // 5. Calculate perpWallDist

    // 6. Calculate wall height

    // 7. Draw the wall

    x++;
}
*/
