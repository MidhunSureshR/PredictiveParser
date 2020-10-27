#!/usr/bin/env python3
import sys

skip = False
for l in sys.stdin:
    if not skip:
        sys.stdout.write(l)
    if l.startswith("# "):
        toks = l.strip().split(" ")
        linenum, filename = toks[1:3]
        flags = toks[3:]
        skip = "3" in flags
