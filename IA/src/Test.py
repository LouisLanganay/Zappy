#!/usr/bin/env python3
# Importing the libraries

from ParseArgs import ParseArgs


# Test 1 
argv = ["./zappy_ai", "-p", "3001", "-n", "name", "-h", "localhost"]

parse_args = ParseArgs()
host, port, name = parse_args.parse(argv[1:])
assert host == "localhost", f"Expected host to be 'localhost', but got '{host}'"
assert port == 3001, f"Expected port to be 3001, but got {port}"
assert name == "name", f"Expected name to be 'name', but got '{name}'"

print("Test 1 passed")
