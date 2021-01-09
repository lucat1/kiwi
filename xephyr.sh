#!/bin/sh -e

make clean
make dev
# make debug

D=${D:-80}
Xephyr +xinerama +extension RANDR -screen 1280x720 :$D &
sleep 1

export DISPLAY=:$D

./kiwi
# gdb -r ./kiwi 
