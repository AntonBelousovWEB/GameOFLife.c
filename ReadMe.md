# Game of Life

Welcome to the GPU implementation of Conway's Game of Life! This project explores the world of graphics programming using raylib and GLSL shaders.

<img src="https://i.ibb.co/FY85N47/2024-02-09-180223.png" />

## Overview:

- **Project Description:** This project implements Conway's Game of Life using GPU acceleration. The game is a cellular automaton where cells on a grid evolve over time based on a set of rules.
- **Technology Stack:**
  - **raylib:** A simple and easy-to-use library for game development in C. It provides a range of functionalities for graphics, input handling, and more.
  - **GLSL:** The OpenGL Shading Language is used for writing shaders that run on the GPU. In this project, GLSL shaders are employed to implement the rules of the Game of Life.
  
In this project, the game evolves on the GPU, offering potentially significant performance improvements compared to traditional CPU-based implementations.

### Instructions:
- Zoom:
  - To zoom in, use the `+` key - `MUMLK`.
  - To zoom out, use the `-` key - `MUMLK`.
  - Press the corresponding key again to stop zooming or panning.

- Switch Colors:
  - To switch forward use `->` key.
  - To go back use `<-` key.

- Play Sound:
  - To play sounds use `SPACE` key.
  - To upload your music use the `muz` folder in the `resources` folder
  - Use `.ogg` files named `sound` + `index file`. Example: `sound1.ogg`.

- Respawn:
  - To turn on respawn pixels use `Right CTRL` key.
  - To turn off respawn pixels use `Right CTRL` key.

Happy coding!