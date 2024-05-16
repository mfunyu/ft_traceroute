#!/bin/bash

REAL="inetutils-traceroute"
MINE="../ft_traceroute"

if [ ! $1 ]; then
	echo "Usage: $0 <test>"
	exit 1
fi
test="$1"

FILE=$MINE ./$test > mine 2>&1
FILE=$REAL ./$test > real 2>&1
sed -i "s!${MINE}!${REAL}!g" mine
sed -i "s!ft_traceroute!${REAL}!g" mine
diff -y --width=150 mine real