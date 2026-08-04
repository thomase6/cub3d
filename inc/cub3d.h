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
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

//		Error Messages		//
# define ARG_COUNT "Error\nWrong number of arguments\n"
# define INVALID_ARG "Error\nInvalid argument\n"
# define OPEN_FAILED "Error\nFailed to open file\n"

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

# define WIN_WIDTH      800
# define WIN_HEIGHT     600

# define TILE_SIZE      32
# define PLAYER_SIZE    5
# define SPEED		0.01
# define ROT_SPEED	0.01
# define RADIUS		0.1
/*
typedef struct s_map
{
	char	*line;
	int		fd;
	
} t_map;
*/

typedef struct s_map
{
	char	**grid;
	int	width;
	int	height;	
}	t_map;

typedef struct s_player
{
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


//		Utils					//
void	print_error(char *msg);

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
void	draw_minimap_player(t_game *game);
void	draw_minimap_background(t_game *game);
void	draw_minimap_rays(t_game *game);
void	ray_casting(t_game *game);
void	init_player(t_game *game);
void	cleanup_game_mlx(t_game *data); // not shure which to use game or data!
//void    render(t_game *game);
//void    move_player(t_game *game);
//void    draw_map(t_game *game);
//void    handle_key(int keycode, t_game *game);

#endif
