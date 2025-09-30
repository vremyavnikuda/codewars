#!/bin/bash

echo "Testing interaction between bash and C programs..."

# Make sure executables have proper permissions
chmod +x hello_world help_program create_file delete_file read_hash_file 2>/dev/null

echo ""
echo "=== Testing Hello World Program ==="
if [ -f "./hello_world" ]; then
    echo "Running hello_world..."
    ./hello_world
    echo "Exit code: $?"
else
    echo "hello_world executable not found (compile first)"
fi

echo ""
echo "=== Testing Help Program ==="
if [ -f "./help_program" ]; then
    echo "Running help_program..."
    ./help_program
    echo "Exit code: $?"
else
    echo "help_program executable not found (compile first)"
fi

echo ""
echo "=== Testing File Creation ==="
if [ -f "./create_file" ]; then
    echo "Creating test_file.txt..."
    ./create_file "test_file.txt" "This is a test file content."
    echo "Exit code: $?"
else
    echo "create_file executable not found (compile first)"
fi

echo ""
echo "=== Testing File Reading and Hash Calculation ==="
if [ -f "./read_hash_file" ]; then
    echo "Reading test_file.txt and calculating hash..."
    ./read_hash_file "test_file.txt"
    echo "Exit code: $?"
else
    echo "read_hash_file executable not found (compile first)"
fi

echo ""
echo "=== Testing File Deletion ==="
if [ -f "./delete_file" ]; then
    echo "Deleting test_file.txt..."
    ./delete_file "test_file.txt"
    echo "Exit code: $?"
else
    echo "delete_file executable not found (compile first)"
fi

echo ""
echo "Test completed. Note: This script will work properly on Linux or WSL."