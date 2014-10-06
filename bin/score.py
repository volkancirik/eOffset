#!/usr/bin/env python
import sys

hit = 0
miss = 0
for line1,line2 in zip(open(sys.argv[1]),open(sys.argv[2])):
	if line1.strip().lower() == line2.strip().split():
		hit +=1
	else:
		miss +=1
print hit*1.00/(hit+miss)
