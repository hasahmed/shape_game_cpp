#!/usr/local/bin/python3

import os
import subprocess
from os import listdir
from os.path import isdir, join

DIST_PATH = 'dist'
INCLUDE = 'include'
SHAPE_GAME_HEADER = 'shapegame.hpp'
CXX = "clang++"
CXXFLAGS = '-std=c++17 -E -P'


def has_include():
    dirs = listdir('.')
    for dir in dirs:
        if isdir(dir):
            if dir == INCLUDE:
                return True
    return False

if not has_include():
    os.chdir('..')
if not has_include():
    print('Expected include/ diretory in current or parent directory')
    exit()
try:
    os.mkdir(DIST_PATH)
except:
    pass

# subprocess.Popen(CXX, CXXFLAGS.split(), join(INCLUDE, SHAPE_GAME_HEADER), '>', join(DIST_PATH, SHAPE_GAME_HEADER))
os.system("%s %s %s > %s"
            %(
                CXX,
                CXXFLAGS,
                join(INCLUDE,SHAPE_GAME_HEADER),
                join(DIST_PATH, SHAPE_GAME_HEADER)
            )
        )
