#!/usr/bin/bash
echo "making setlevel.c from editor"
rm src/setlevel.c
python compile_level.py
echo "building for cg"
fxsdk build-cg
echo "done"
