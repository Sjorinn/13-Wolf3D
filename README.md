# 13-Wolf3D

![image](https://user-images.githubusercontent.com/45825944/221217326-02dcc20c-3b84-4c52-b4fa-14f76f3bfa98.png)

A Wolfeinstein-like renderer made in C using minilibX, with textures, basic
lighting and basic map files.

## Compiling
Run `make` and you're set. Runs on Mac OS X and Linux (with XServer).
Make sure to enable set the `HI_RES = 1` macro if you want to use the high
resolution textures included.

## Running
Run `./wolf3d [map_file]`, a window should appear. You can navigate through the
map using the arrow keys. Exit by closing the window or pressing ESC.

## Map file format
It's a very simple format. Open a file in your favorite text editor, make sure
you have a grid of integers (each one being it's block ID), and it should work
right out of the box. Spawn position is the first empty space available from the
top left.

```
1 1 1 1 1
1 0 2 0 1
1 0 0 0 1
1 1 1 1 1
