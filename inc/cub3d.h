/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 10:05:44 by texenber          #+#    #+#             */
/*   Updated: 2026/07/28 13:29:01 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>


//		Error Messages		//
# define ARG_COUNT "Error\nWrong number of arguments\n"
# define INVALID_ARG "Error\nInvalid argument\n"
# define OPEN_FAILED "Error\nFailed to open file\n"
# define TEXT_DUP "Error\nTexture duplicate found\n"
# define COLOR_DUP "Error\nColor duplicate found\n"
# define STRDUP_FAIL "Error\nft_strdup failed to malloc\n"
# define INV_TEXT "Error\nInvalid texture\n"
# define INV_COLOR "Error\nInvalid color\n"
# define SPLIT_FAIL "Error\nft_split failed\n"
# define EMPTY_COLOR "Error\nColor missing\n"
# define INV_COLOR_AMOUNT "Error\nThe color must be displayed in the format rrr,ggg,bbb"
# define EMPTY_LINE_IN_MAP "Error\nEmpty line detected in the map"
# define INVAL_MAP_CHAR "Error\nInvalid map character found in a map line."
# define NOT_MAP_LINE "Error\nFound an invalid line in the map grid."

typedef struct s_map
{
	// char	*line;
	// int		fd;
	int		f_color; // floor color
	int		c_color; // ceiling color
	bool	has_floor;	// flag for duplicate check
	bool	has_ceiling; // flag for duplicate check
	bool	map_started;	// flag to check if the parsing of the map has started
	char	*north;	// NO texture
	char	*south;	// SO texture
	char	*east; // EA texture
	char	*west; // WE texture
	char	**map_grid; // all the map lines
	int		map_height;
	int		map_width;
} t_map;

typedef struct s_player
{} t_player;

typedef struct s_game
{
	t_map		map;
	t_player	player;
} t_game;

//		Parser folder	//

//		parser.c		//

int	parser(t_game *data, int ac, char **av);
int read_file(t_game *data, char **av);
int	validate_arg(char **av);

//		texture_parse.c	//

int	parse_textures(t_game *data, char *line);
int	texture_extraction(char **target, char *line);
int validate_textures(char *arg);

//		color_parse.c	//

int	parse_colors(t_game *data, char *line);
int	color_extraction(int *target, bool *flag,char *line);
int	validate_and_store_colors(char **s, int *target);

//		map_parse.c		//

int	parse_map(t_game *data, char *line);
int	is_mapchar(char c);
int	store_grid_and_player(t_game *data, char *line);

//		Utils folder	//

//		error_handle.c	//

void	print_error(char *msg);
void	free_arr(char **array);


#endif