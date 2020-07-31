#!/bin/sh -e

cleanup() {
	rm sxhkdrc
	exit 0
}

trap 'cleanup' INT

make

D=${D:-80}

Xephyr -screen 1600x800 :$D&
sleep 1

export DISPLAY=:$D
cp examples/sxhkdrc sxhkdrc

sxhkd -c sxhkdrc &
./kiwi
