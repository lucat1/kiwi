#!/bin/sh -e

make debug

D=${D:-80}
Xephyr -br -ac -noreset -screen 1200x800 :$D&
sleep 1

export DISPLAY=:$D

./kiwi
# gdb -r ./kiwi 
