#!/usr/bin/env python3

import zipfile
import os
import util

util.cd_root()

ARCH_NAME = 'shapegame.zip'

with zipfile.ZipFile(ARCH_NAME, 'w') as dist_zip:
	for file in os.listdir(util.DIST_PATH):
		dist_zip.write(os.path.join(util.DIST_PATH, file), os.path.join('shapegame', file))