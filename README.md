# Frog Game

## Play Online

The game can be played directly in the browser through itch.io, without requiring any installation.

#### Video Demo: <URL HERE>

#### Description

Frog Game is my final project for Harvard's CS50x. It is a 2D platformer developed in C using the Raylib graphics library. Rather than recreating a traditional platformer, I wanted to build a game around a single mechanic: charging jumps. The player controls a frog that can charge its jump by holding the space bar, with the jump force increasing the longer the key is held. Mastering the timing and strength of each jump is the core challenge of the game.

The objective is to climb the tower as high as possible without falling. Each platform reached awards points based on the player's progress , encouraging the player to keep progressing upward. 

One aspect I wanted to focus on was making the gameplay feel satisfying. Whenever the frog lands on a platform, a sound is triggered and the platforms and frog all move down, creating the illusion that the frog has climbed higher. 

From a technical perspective, one of the biggest challenges was procedural platform generation. Instead of constantly creating and destroying platforms, platforms that move below the screen are recycled. When recycled, each platform is repositioned above the highest existing platform with a randomized spacing, creating the illusion of an infinite level while keeping memory usage constant.

Another challenge was organizing the project itself. Early in development, almost all of the code lived inside `main.c`, which quickly became difficult to maintain as new features were added. I performed several large refactors throughout development, gradually moving responsibilities into separate modules such as player logic, platform management, wall handling and configuration. This resulted in a much cleaner architecture that makes adding new mechanics significantly easier.

One additional challenge was bringing the project to the web. Since the game was originally developed as a native C application using Raylib, creating a browser version required learning how to compile the project with Emscripten and adapting the build process to WebAssembly. Although this did not require major changes to the game logic itself, understanding the toolchain and configuring the project correctly was a valuable learning experience. The result is a playable browser version that can be accessed without requiring users to download or install the game.

## File Structure

* `main.c` initializes Raylib, runs the game loop and coordinates the different game systems.
* `frog.c` and `frog.h` implement the player's movement, jump charging, physics, collision handling and animation.
* `platforms.c` and `platforms.h` manage platform creation, rendering, updating and procedural recycling.
* `walls.c` and `walls.h` handle wall rendering and wall collision logic.
* `score.c` and `score.h` manage the scoring system, including score updates and rendering.
* `config.h` centralizes game constants such as dimensions, movement parameters and gameplay configuration.
* `assets/` contains sprites and sound effects used throughout the game.
* `Makefile` automates compilation of the project.

## Design Choices

Throughout development I prioritized readability and maintainability over simply making the game work. Separating functionality into modules allowed each source file to have a single responsibility, making the codebase easier to navigate and extend.

Another important design decision was recycling platforms instead of allocating new ones. Since the number of visible platforms never changes, reusing existing objects avoids unnecessary allocations while simplifying memory management.
