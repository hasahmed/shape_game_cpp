#!/usr/local/bin/python3

import os
import glob
import subprocess
from os import listdir
from os.path import isdir, join

DIST_PATH = 'dist'
INCLUDE = 'include'
OUT_HEADER = 'shapegame.hpp'


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

headers = glob.glob(join(INCLUDE, "*.hpp"))
includes = set()
other_lines = []
for header in headers:
	with open(header) as header_file:
		for line in header_file:
			if "#include <" in line:
				includes.add(line)
			else:
				if (not '#include "' in line) and (not '#pragma' in line):
					other_lines.append(line)

out_header = open(join(DIST_PATH, OUT_HEADER), "w+")

out_header.write('#pragma once\n')
for line in includes:
	out_header.write(line)
for line in other_lines:
	out_header.write(line)

out_header.close()