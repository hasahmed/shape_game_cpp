#!/usr/bin/env python3

import util

# import os
# import glob
# import subprocess
# from os import listdir
# from os.path import isdir, join

util.cd_root()

DIST_PATH = 'dist'
INCLUDE = 'include'
OUT_HEADER = 'shapegame.hpp'


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
