/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 10:05:44 by texenber          #+#    #+#             */
/*   Updated: 2026/08/13 19:22:32 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
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
# define MISS_CONFIG "Error\nMissing argument in the map file."
# define MAP_FAIL "Error\nFailed to validate map."
# define NO_PLAYER "Error\nNo player found."
# define TOO_MANY_PLAYERS "Error\nToo many players found."

// KEY_CODES                         //
# define ESC	65307
# define KEY_W	119  // forward
# define KEY_A	97   // strafe left
# define KEY_S	115  // strafe right
# define KEY_D	100  // backwards
# define KEY_LEFT	65361	// turn left
# define KEY_RIGHT	65363   // turn right
# define KEY_UP		65362	// UP	
# define KEY_DOWN	65364   // DOWN  both not needed !!

# define WIN_WIDTH      1024
# define WIN_HEIGHT     512

# define MINI_MAP_RAYS	36	 
# define MINI_CENTER_X	128
# define MINI_CENTER_Y	64
# define MINI_TILE	8

# define TILE_SIZE      32
# define PLAYER_SIZE    5
# define SPEED		0.01
# define ROT_SPEED	0.01
# define RADIUS		0.1

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
	int		height;
	int		width;
} t_map;

// typedef struct s_map
// {
// 	char	**grid;
// 	int	width;
// 	int	height;	
// }	t_map;

typedef struct s_player
{
	char	p_dir;	// Parsing stores the direction the player is facing.
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int	move_forward;
	int	move_backward;
	int	turn_left;
	int	turn_right;
}	t_player;

typedef struct s_next_position
{
	float	next_x;
	float	next_y;	
}	t_next_position;

typedef struct s_raycasting
{
	int	mapX;
	int	mapY;
	int	stepX;
	int	stepY;
	int	side;
	int	hit;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;	
} t_raycasting;

typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;

	int		map_x;
	int		map_y;

	float	side_dist_x;
	float	side_dist_y;

	float	delta_dist_x;
	float	delta_dist_y;

	int		step_x;
	int		step_y;

	int		side;
}	t_ray;

typedef struct s_mini_ray
{
	float	scale;
	float	step;
	float	fov;
	float	angle;
	float	start_angle;
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_x;
	float	ray_y;
}	t_mini_ray;

typedef struct s_game
{
	void	*mlx;    // from mlx
	void	*win;
	void	*img;
	char	*addr;
	int	bpp;      // from mlx
	int	line_len; // from mlx
	int	endian;   // from mlx
	t_map		map;
	t_player	player;
} t_game;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	size;
	int	tile_x;
	int	tile_y;
 }   t_minimap;
 
//		Parsing Functions		//
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

//		Utils					//

//		error_handling.c		//
void	print_error(char *msg);
void	free_arr(char **array);

//		init					//
// Initialization                                  //
int	init_game(t_game *game);
int	close_game(t_game *game);
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);
int	update(t_game *game);
int	is_wall(t_game *game, float x, float y);
void	clear_image(t_game *game);
void	collision_check(t_game *game, t_next_position *movement, float radius);
void	render_game(t_game *game);
void	display_frame(t_game *game);
void	rotate_player(t_game *game, double angle);
void	move_player(t_game *game, t_next_position * movement, int direction, float speed);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_player_direction(t_game *game);
void	draw_direction(t_game *game);
void	draw_ray(t_game *game);
void	ray_caster(t_game *game);
void	draw_minimap(t_game *game);
void	draw_minimap_floor(t_game *game, int map_x, int map_y);
void	draw_minimap_player(t_game *game);
void	draw_minimap_background(t_game *game);
void	draw_minimap_tile(t_game *game, int map_x, int map_y);
void	draw_minimap_rays(t_game *game);
void	ray_casting(t_game *game);
void	init_player(t_game *game);
void	cleanup_game_mlx(t_game *data); // not shure which to use game or data!
//void    render(t_game *game);
//void    move_player(t_game *game);
//void    draw_map(t_game *game);
//void    handle_key(int keycode, t_game *game);

#endif
