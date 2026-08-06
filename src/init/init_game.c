/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: texenber <texenber@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:32:22 by stbagdah          #+#    #+#             */
/*   Updated: 2026/08/06 14:50:47 by texenber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* 
1. start mlx
2. create window
3. create image buffer
4. connect map
5. setup player
6. register events
7. start loop
*/
char *map[11] = {
    "1111111111111111111111111",
    "1000000000000000000000001",
    "10111001000000000000110001",
    "1010000100110000000000001",
    "1010110100000000000000001",
    "1010000101111011111100111",
    "1010011101  101  11100111",
    "1000000001111011111100111",
    "1000000000000000000000001",
    "1111111111111111111111111",
    NULL
};
/*
update
 ├── clear_image()
 ├── rotate_player()
 ├── move_player()
 ├── collision_check()
 ├── render_game()
 └── display_frame()
 */
 
int update(t_game *game)
{
	t_next_position	movement;
	
   	clear_image(game);
    movement.next_x = game->player.x;
    movement.next_y = game->player.y;
    if (game->player.turn_left)
	rotate_player(game, -ROT_SPEED);
    if (game->player.turn_right)
	rotate_player(game, ROT_SPEED);
    if (game->player.move_forward)
   	move_player(game, &movement, 1, SPEED);
    if (game->player.move_backward)
	move_player(game, &movement, -1, SPEED);
    collision_check(game, &movement, RADIUS);
    render_game(game);
    display_frame(game);
    return (0);
}

int init_game(t_game *game)
{
    game->mlx = mlx_init();          // start MLX connection to the graphics system
    if (!game->mlx)		     // a tool that lets you talk to the screen	
        return (EXIT_FAILURE);       // program -> MLX -> OS -> screen
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D"); // creating window on the screen
    if (!game->win)                                           // size plus title USE VARIABLE!!
    {
        free(game->mlx);
        return (EXIT_FAILURE);
    }
    game->img = mlx_new_image(game->mlx, 800, 600);    //fake screen in memory FRAMEBUFFER
    game->addr = mlx_get_data_addr(game->img,     // draw pixel by pixel in memory than push to window
        &game->bpp,   // addr -> pointer to pixel in memory bpp-> bits per pixel usualy 32
        &game->line_len,  // how many bytes per row given from mlx plus minus padding
        &game->endian);   // byte order -> little endian here back to fron Ox11223344 -> 44332211
    // game->map.map_grid = map; // assigning static map in game struct game->map->grid->"11100101010111..."
    init_player(game); // now player exist inside game at pos x,y
    mlx_hook(game->win, 17, 0, close_game, game); // ESC close game
    mlx_hook(game->win, 2, 1L << 0, key_press, game); // when key is pressed->key_press()
    mlx_hook(game->win, 3, 1L << 1, key_release, game); // when key is release->key_release()
    mlx_loop_hook(game->mlx, update, game); // call update every frame (60 per sec)
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0); // pushes buffer to screen
    mlx_loop(game->mlx); // hand control to MLX forever program runs now in MLX
    return (EXIT_SUCCESS);
}
