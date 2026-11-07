/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stbagdah <stbagdah@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 12:25:39 by stbagdah          #+#    #+#             */
/*   Updated: 2026/10/05 12:26:33 by stbagdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (EXIT_FAILURE);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	load_textures(t_game *game)
{
	if (load_one(game, &game->tex[NO], game->map.north)
		|| load_one(game, &game->tex[SO], game->map.south)
		|| load_one(game, &game->tex[WE], game->map.west)
		|| load_one(game, &game->tex[EA], game->map.east))
		return (print_error(INV_TEXT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
}
