#!/bin/bash

echo "Compiling C programs for Linux system calls demonstration..."

# Compile hello_world.c
gcc -o hello_world hello_world.c
if [ $? -eq 0 ]; then
    echo "✓ hello_world compiled successfully"
else
    echo "✗ Failed to compile hello_world.c"
fi

# Compile help_program.c
gcc -o help_program help_program.c
if [ $? -eq 0 ]; then
    echo "✓ help_program compiled successfully"
else
    echo "✗ Failed to compile help_program.c"
fi

# Compile create_file.c
gcc -o create_file create_file.c
if [ $? -eq 0 ]; then
    echo "✓ create_file compiled successfully"
else
    echo "✗ Failed to compile create_file.c"
fi

# Compile delete_file.c
gcc -o delete_file delete_file.c
if [ $? -eq 0 ]; then
    echo "✓ delete_file compiled successfully"
else
    echo "✗ Failed to compile delete_file.c"
fi

# Compile read_hash_file.c
gcc -o read_hash_file read_hash_file.c
if [ $? -eq 0 ]; then
    echo "✓ read_hash_file compiled successfully"
else
    echo "✗ Failed to compile read_hash_file.c"
fi

echo ""
echo "Compilation process completed."
echo "Note: These programs use Linux system calls (open, read, write, unlink) and"
echo "are intended to run on a Linux system or WSL (Windows Subsystem for Linux)."