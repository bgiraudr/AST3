#!/bin/sh
echo "#define LEVEL_MAX $(ls editor/levels/[^0]*.lvl | wc -l)
#define PLAYER_HEIGHT 11
#define FPS 70" > include/define.h
