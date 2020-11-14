#!/usr/bin/bash
echo "making setlevel.c from editor"
rm src/setlevel.c
python compile_level.py
echo "done"
echo "making times.c from times.lvl"
rm src/times.c
python time.py
echo "done"
echo "building for cg"
fxsdk build-cg
echo "done"
