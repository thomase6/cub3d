
*This project has been created as part of the 42 curriculum by texenber and stbagdah.*

# cub3D

## Description

**cub3D** is a 3D graphical project inspired by *Wolfenstein 3D*, the iconic 1992 first-person shooter developed by id Software.

The objective of this project is to create a dynamic first-person maze exploration experience using **raycasting** and the **MiniLibX** graphical library in C.

The core idea is to transform a two-dimensional map into a three-dimensional first-person perspective. This is achieved by casting rays from the player's position towards the environment and calculating the distance to the nearest wall intersection.

These distances determine the height of vertical wall slices rendered on the screen, creating the illusion of depth. By repeating this process across the screen, a 3D environment can be generated from a simple 2D grid.

### Features

- **Scene Parsing:** Reads `.cub` files containing wall texture paths, floor and ceiling colors, and map information.
- **Map Validation:** Checks configuration elements, validates RGB values, verifies texture files, ensures a single player starting position, and checks that the map is enclosed by walls.
- **Raycasting:** Converts the 2D map into a first-person 3D perspective.
- **Textured Walls:** Supports different textures for North, South, East, and West-facing walls.
- **Player Movement:** Allows movement forward, backward, left, and right.
- **Camera Rotation:** Allows the player to look around by rotating the camera.
- **Collision Detection:** Prevents the player from walking through walls or outside the playable map.
- **MiniLibX Graphics:** Handles window creation, image rendering, and keyboard events.

---

## Instructions

### Prerequisites

The project requires:

- Linux environment with the X11 windowing system.
- C compiler (`cc`).
- `make`.
- MiniLibX graphics library.
- X11 development libraries and the required MiniLibX dependencies.

### Installation

Clone the repository:

```bash
git clone <repository-url> <name>
cd <name>
```

### Compilation

Compile the project using the Makefile:

```bash
make
```

This generates the `cub3D` executable.

### Makefile Rules

| Command | Description |
|---|---|
| `make` | Compiles the project. |
| `make all` | Builds the executable. |
| `make clean` | Removes object files. |
| `make fclean` | Removes object files and the executable. |
| `make re` | Performs a complete recompilation. |
| `make debug` | Performs a complete recompilation with -g flag. |

### Execution

Run the executable with a valid `.cub` scene file:

```bash
./cub3D maps/example.cub
```

The program loads and validates the scene configuration and map before initializing the graphical environment.

---

## Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `↑` | Move forward |
| `↓`  | Move backward |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit the game |
| Window `X` | Close the game |

---

## Map Format (.cub)

A `.cub` file describes the scene configuration and the 2D map.

It consists of two sections:

1. Scene configuration.
2. Map layout.

The scene configuration must be defined before the map.

### Example Configuration

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,3
C 225,30,0

1111111111
1000000001
1000100001
1000N00001
1000000001
1111111111
```

### Scene Elements

| Identifier | Description |
|---|---|
| `NO` | North wall texture. |
| `SO` | South wall texture. |
| `WE` | West wall texture. |
| `EA` | East wall texture. |
| `F` | Floor color in RGB format. |
| `C` | Ceiling color in RGB format. |

### Map Characters

| Character | Description |
|---|---|
| `1` | Wall. |
| `0` | Walkable floor. |
| `N` | Player starting position facing North. |
| `S` | Player starting position facing South. |
| `E` | Player starting position facing East. |
| `W` | Player starting position facing West. |
| ` ` | Empty space. |

### Map Validation Rules

- The map must contain exactly one player starting position.
- The map must be surrounded by walls.
- Only permitted characters are allowed.
- Walkable areas must not be exposed to the outside of the map.
- The map must be the last element in the `.cub` file.
- Irregular map dimensions must be handled correctly.

---

## Resources

The following resources were useful for understanding and implementing the concepts behind cub3D.

### Documentation & Tutorials

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html) — Detailed explanations of raycasting, DDA, camera mathematics, wall projection, and texture mapping.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Documentation covering windows, images, events, and graphical operations using MiniLibX.
- [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) — The classic first-person shooter that inspired this project.
- [42 School](https://42.fr/) — Information about the 42 curriculum and its educational approach.

### AI Usage

AI tools were used as supplementary assistance during the development of this project.

Their usage included:

- **Documentation:** Helping understand technical concepts related to raycasting, DDA algorithms, MiniLibX, and C programming.
- **Debugging Assistance:** Helping analyze compiler errors, runtime issues, and potential implementation problems.
- **Concept Clarification:** Explaining mathematical concepts such as ray direction, wall distances, camera projection, and texture mapping.
- **README Preparation:** Assisting with the organization, wording, and formatting of this documentation.

---

