#!/bin/sh -e

make dev
# make debug

D=${D:-80}
Xephyr +extension RANDR -resizeable -screen 1280x720 :$D &
sleep 1

export DISPLAY=:$D

./kiwi
# gdb -r ./kiwi 
