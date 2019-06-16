import os
from os import listdir
from os.path import isdir

DIST_PATH = 'dist'
INCLUDE = 'include'


def has_include():
    dirs = listdir('.')
    for dir in dirs:
        if isdir(dir):
            if dir == INCLUDE:
                return True
    return False

def cd_root():
    if not has_include():
        os.chdir('..')
    if not has_include():
        print('project root directory was expected in parent directory at highest. Run from tools/ or project root')
        exit()
