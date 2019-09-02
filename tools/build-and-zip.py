#!/usr/bin/env python3


import platform
import os
import util


util.cd_root()


system = platform.system()
dist_name = ""
make_arg = "dist-"

if system == "Darwin":
    dist_name = "mac"
elif system == "Linux":
    dist_name = "linux"
elif system == "Windows":
    dist_name = "win"
else:
    print("Error. Don't know how to handle OS [%s]" % system)
    exit()


make_arg += dist_name
try:
    os.system("make %s" % make_arg)
except(e):
    print("There has been an error")
    print(e)

os.chdir('tools/')

# lazy way of running code that wasn't built to be called
# when a module is imported its code is run
import zip_dist
