#!/bin/zsh

set -eux

dir="$(dirname $2)"
base="$(basename $2 .cpp)"

g++ -g -ftrapv -fsanitize=undefined -fsanitize=address -Wall $dir/$base.cpp -o $dir/$base -I . -I ./library -I ./ac-library -D DEBUG -std=gnu++17 -O2

oj-bundle $dir/$base.cpp -I . -I library -I ac-library >$dir/${base}_expanded.cpp

cd $dir

if [ $1 = "test" ] || [ $1 = "submit" ]; then
  oj t -c ./$base -e 1e-6
fi

if [ $1 = "submit" ] || [ $1 = "force-submit" ]; then
  oj s ${base}_expanded.cpp
fi
