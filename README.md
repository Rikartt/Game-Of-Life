# Game-Of-Life
Coding the game of life in different languages, starting with Python.
# Python

*Dependencies*
- Pygame

*Explanation*
The PygameGOL.py file is the main Python file, with a fully functioning Conway's Game Of Life that's interactive and can be used.
This file is in turn dependent on the separate GOL.py file, defining the basic grid logic for the game.

# Javascript

The plan is to use JS canvas to make the game of life. Should be easy as we just have to code the same functions as the python used.

# C
  - [X] Game of Life logic and text based version finished but still have to make a nice GUI etc.
  - [X] Raylib GUI version of the Game Of Life finished! C Part of this project is finished!
Compile:
Windows: x86_64-w64-mingw32-gcc raylibGOL.c -o life.exe \
  -I/usr/x86_64-w64-mingw32/include \
  -L/usr/x86_64-w64-mingw32/lib \
  -lraylib -lopengl32 -lgdi32 -lwinmm -lm -mwindows
Archlinux: gcc raylibGOL.c -o life $(pkg-config --cflags --libs raylib) -lm
./life

# Roadmap

- [X] Python
- [X] Javascript/WebGL
- [X] C
- [ ] C++
- [ ] Rust
- [ ] Golang