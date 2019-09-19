#!/usr/bin/env python3

import zipfile
import os
import util

util.cd_root()


ARCH_NAME = 'shapegame.zip'
ZIP_DIST = 'zip-dist'

def create_archive():
	with zipfile.ZipFile(ARCH_NAME, 'w') as dist_zip:
		os.chdir(util.DIST_PATH)
		for root, dirs, files in os.walk('.'): #every file in dist-libs
			for file in files:
				dist_zip.write(os.path.join(root, file), os.path.join('shapegame', root, file))
		os.chdir('..')
		os.chdir(util.INCLUDE)
		for root, dirs, files in os.walk('.'): #every file in include/
			for file in files:
				dist_zip.write(os.path.join(root, file), os.path.join('shapegame', util.INCLUDE, root, file))
		os.chdir('..')
		os.chdir(util.DEPS) #in deps
		for root, dirs, files in os.walk('.'): #every file in deps
			for file in files:
				dist_zip.write(os.path.join(root, file), os.path.join('shapegame', util.DEPS, root, file))
		os.chdir('../') #leave directory in same state as before

create_archive()
os.rename(ARCH_NAME, os.path.join(ZIP_DIST, ARCH_NAME))
