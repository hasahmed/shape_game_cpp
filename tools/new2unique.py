import sys
import re

f_name = sys.argv[1]
with open(f_name) as f:
	content = f.readlines()

for line in content:
	line = re.sub(
		r"new",
		r'\b',
		line
	)
	print(line)