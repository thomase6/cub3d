TEMPORARY:

Program Name: cub3D
Files to Submit: All your files
Makefile: all, clean, fclean, re, bonus
Arguments: a map in format *.cub
External Function:
• open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday.
• All functions of the math
library (-lm man man 3 math).
• gettimeofday()
• All functions of the MinilibX
library.
Libft authorized Yes
Description You must create a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective. You have to create this
representation using the ray-casting principles
mentioned earlier.

Goal: You must create a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective. You have to create this
representation using the ray-casting principles
mentioned earlier.


We are supposed to use the Minilibx to generate a 3d representation of the maps in the map folder. To do this we need to learn how to properly format the map with the required information. The map document must also include the address of the textures for each cardinal direction. We must also set the color for both the floor and the ceiling with 2 different color. the map itself must be drawn with 6 possible characters: 0 for an empty space, 1 for a wall and N, E, W, S for their respective cardinal directions which will be the direction that the player is facing in the map.

EX:
111111
100101
101001
1100N1
111111

for the parsing of the map.cub: 

- If the map isn't surrounded by walls (1), return an error.
- Except for the map content, each element can be seperated by one or more empty lines.
- Except for the map each type of information from an element can be seperated by one or more spaces.
- The map content must be the last element in the document but the other elements can be in any order.
- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle.
- Except for the map, each element must begin with its type identifier, followed by its specific information in a STRICT order.

Formating of the elements:
1. Textures:
- North Texture: `NO` ./path_to_the_north_texture
- South Texture: `SO` ./path_to_the_south_texture 
- West Texture: `WE` ./path_to_the_west_texture
- East Texture: `EA` ./path_to_the_east_texture
2. Colors:
- Floor color: `F` (RGB colors in range 0-255): 0, 255, 255
- Ceiling color: `C` (RGB colors in range 0-255): 0, 255, 255

Example *.cub:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture 
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220, 100, 0
C 225, 30, 0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- If the *.cub contains any misconfigurations, the program must exit properly and return "Error\n" followed by an explicit error message of our choice.

requirements for the README.md:

- *This project has been created as a part of the 42 curriculum by texenber and stbagdah*
- Description
- Instructions
- Resources
- AI Usage

Bonus:
- Wall collisions.
- A minimap system.
- Doors which can open and close.
- Animated sprites.
- Rotate the point of view with the mouse.

Division of Work for cub3d

texenber: reads and validates the .cub file, builds the map grid as a 2D array, stores texture paths, colors, and the player's starting position/direction. This is pure C string/file work. Also owns error handling and memory cleanup.

stbagdah: implements the game loop with mlx, the DDA raycasting algorithm, player movement/rotation, and drawing wall slices + floor/ceiling.

The Structs we can use for this are:

- t_game: will hold all the other structures so we can pass this to every single function 
- t_map: This one will hold the parameters of the map and will be the one that will be mostly filled up by the person doing parsing.
- t_player: will hold the information related to the player, from the position to the movement speed and rotation speed.

this 3 structs can be shared because most of the data related from the map comes from the map.cub file which will be parsed and stored in the struct. then we will also use t_player to store the position of the player that is also received from the map.cub file. 