*This project has been created as part of 42 curriculum by texenber and stbagdah.*

# CUB3D

## Description:

To understand how to create your own Wolfenstein 3D, you have to build it yourself!
This project teaches you the fundamentals of raycasting and how to use MiniLibX, a minimal C graphics library primarily used for educational purposes at coding schools like our beloved 42.
The idea is to build a "normal" 2D game (top-down, bird's-eye view) and use raycasting to transform it into a 3D first-person perspective (FPS).
Imagine yourself as a player represented by a square on a 2D map, looking towards a wall. To render this in 3D, you calculate the distance between the player and the wall and use that distance to determine the height of the corresponding vertical wall slice on the screen, creating the illusion of depth.
By repeating this process for every vertical slice of the screen, you can create a 3D environment from a 2D map!

## Instructions:

To get started, first clone the Git repository and navigate into the cub3d directory. Once you're inside the project directory, compile the project by running:
bash
make

After compilation, everything is ready to go! Start the game by running:
bash
./cub3D maps/map0.cub

This will open a new window using MiniLibX, and you'll spawn inside the selected map.
Controls
You can move around using the following keys:
W – Move forward
S – Move backward
A – Turn left
D – Turn right

You can also use the arrow keys on your keyboard to move and look around.
Have fun exploring the maps, running around, and discovering your little 3D world!
 
## Resources:

The following resources were helpful for understanding the concepts behind this project, especially raycasting and how to create a 3D perspective from a 2D map.

### YouTube Videos
Raycasting
Raycasting Tutorial – Video 1 https://www.youtube.com/watch?v=gYRrGTC7GtA
Raycasting Tutorial – Video 2 https://www.youtube.com/watch?v=PC1RaETIx3Y
Raycasting Tutorial – Video 3 https://www.youtube.com/watch?v=NbSee-XM7WA&t=630s

These videos provide a good starting point for understanding raycasting and the mathematics behind rendering a 3D environment from a 2D map.

Happy learning!
















