#!/bin/sh
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
