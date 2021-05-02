#!/bin/sh
echo "#define LEVEL_MAX $(ls editor/levels/[^0]*.lvl | wc -l)
#define PLAYER_HEIGHT 11
#define FPS 70
#define LEVEL_WIDTH 25
#define LEVEL_HEIGHT 14
#define TILE_HEIGHT 16" > generated/include/define.h
python3 compile_levels.py
