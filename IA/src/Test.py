#!/usr/bin/env python3
# Importing the libraries

from ParseArgs import ParseArgs


# Test 1 
argv = ["./zappy_ai", "-p", "3001", "-n", "name", "-h", "localhost"]

parse_args = ParseArgs()
host, port, name = parse_args.parse(argv[1:])
assert host == "localhost"
assert port == 3001
assert name == "name"

