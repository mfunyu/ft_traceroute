#!/bin/bash

# ---------------------------------------------------------------------------- #
# define
THICK="\033[1m"
CYAN="\033[1;36m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[m"
PROMPT="${CYAN}\$>${RESET}"
# ---------------------------------------------------------------------------- #

# set FILE if env var does not exist
if [[ -z "${FILE}" ]]; then
	FILE=../ft_traceroute
	#FILE=inetutils-traceroute
fi

values=(
	abc
	12x
	-1
	0
	1
	10
	11
	60
	61
	254
	255
	256
	65535
	65536
	65537
	11111111111111111
)

options=(
	-f
	-m
	-p
	-q
	-w
)

for option in ${options[@]}; do
	printf "${THICK}[Testing option $option]${RESET}\n"
	for value in "${values[@]}"; do
		printf "${PROMPT} ${FILE} doesnotexist.com ${option} ${value}\n"
		$FILE doesnotexist.com $option $value
	done
	printf "\n"
done