#!/bin/bash
cp shapegame shapegame.hpp
c++-7 -std=c++17 -E -P shapegame.hpp > shapegame.preproc
mkdir -p dist
mv shapegame.preproc dist/shapegame
rm shapegame.hpp
