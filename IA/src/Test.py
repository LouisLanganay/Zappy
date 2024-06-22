#!/usr/bin/env python3
# Importing the libraries

from ParseArgs import ParseArgs
from Main import MainClient

# Test 1 fonctionelle
argv = ["./zappy_ai", "-p", "3001", "-n", "name", "-h", "localhost"]

parse_args = ParseArgs()
host, port, name = parse_args.parse(argv[1:])
assert host == "localhost", f"Expected host to be 'localhost', but got '{host}'"
assert port == 3001, f"Expected port to be 3001, but got {port}"
assert name == "name", f"Expected name to be 'name', but got '{name}'"
print("Test 1 passed")


## Test 3 unitaire

host, port, name = parse_args.parse(['-p', '8080', '-n', 'test', '-h', 'localhost'])
assert port == 8080, f"Expected port to be '8080', but got {port}"
assert name == 'test', f"Expected name to be 'test', but got {name}"
assert host == 'localhost', f"Expected host to be 'localhost', but got {host}"
print("Test 2 passed")

#def test_parse_invalid_args():
#    parser = ArgumentParser()
#    result = parser.parse(['-x', 'value'])
#    assert result == 84, f"Expected result to be 84, but got {result}"


## Test 4 unitaire

#host, port, name = parse_args.parse(['-p', '8080', '-n', 'test', '-h', 'localhost'])
#result = parse_args.parse(['-x', 'value'])
#assert result == 84, f"Expected result to be 84, but got {result}"

## Test 5 unitaire

try:
    assert parse_args.parse(['-helpzdza'])
except SystemExit:
    print("Test 5 passed")
    pass  # Expected behavior
else:
    assert False, "Expected SystemExit"

# Test 6 unitaire
#result = parse_args.parse(['-p'])
#assert result == 84, f"Expected result to be 84, but got {result}"




# Connect and get Slot

#test 1

argv = ["./zappy_ai", "-p", "3001", "-n", "name", "-h", "localhost"]
parse_args = ParseArgs()
host, port, name = parse_args.parse(argv[1:])
mainClient = MainClient(host, port, name)
available_slots = mainClient.connect_and_get_slots()
assert MainClient.send(name + '\n') == 0, "OKEY KOALA"

