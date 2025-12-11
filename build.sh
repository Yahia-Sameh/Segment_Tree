#!/bin/bash

echo "=== Building Segment Tree Examples ===\n"

echo "Compiling example.cpp..."
g++ -std=c++17 example.cpp -o example
if [ $? -eq 0 ]; then
  echo "  ✓ Success: Created ./example"
else
  echo "  ✗ Failed to compile example.cpp"
  exit 1
fi

echo "\nCompiling test.cpp..."
g++ -std=c++17 test.cpp -o test
if [ $? -eq 0 ]; then
  echo "  ✓ Success: Created ./test"
else
  echo "  ✗ Failed to compile test.cpp"
  exit 1
fi

echo "\n=== Build Complete ==="
echo "Run: ./example   # For a simple example"
echo "Run: ./test      # To run tests"
