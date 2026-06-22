/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 10:05:44 by texenber          #+#    #+#             */
/*   Updated: 2026/06/22 14:23:48 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>


//		Error Messages		//
# define ARG_COUNT "Error\nWrong number of arguments\n"
# define INVALID_ARG "Error\nInvalid argument\n"
# define OPEN_FAILED "Error\nFailed to open file\n"

typedef struct s_map
{
	char	*line;
	int		fd;
	
} t_map;

typedef struct s_player
{} t_player;

typedef struct s_game
{
	t_map		map;
	t_player	player;
} t_game;

//		Parsing Functions		//

int	parser(t_game *data, int ac, char **av);


//		Utils					//

void	print_error(char *msg);


#endif