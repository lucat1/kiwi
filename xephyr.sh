#!/bin/sh -e

make debug

D=${D:-80}
Xephyr +extension RANDR -screen 1280x720 :$D &
sleep 1

export DISPLAY=:$D

# ./kiwi
gdb -r ./kiwi 
