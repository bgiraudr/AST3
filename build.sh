#!/bin/sh
echo "making define.h from editor"
rm include/define.h
echo "#define LEVEL_MAX $(ls editor/levels/[^0]*.lvl | wc -l)
#define PLAYER_HEIGHT 11
#define FPS 70" > include/define.h
echo "done"
echo "making setlevel.c from editor"
rm src/setlevel.c
python3 compile_level.py
echo "done"
echo "making times.c from times.lvl"
rm src/times.c
python3 time.py
echo "done"
echo "building for cg"
fxsdk build-cg
echo "done"
