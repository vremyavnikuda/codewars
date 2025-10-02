#!/bin/bash

# Script to compile all IPC implementations

echo "Compiling all IPC implementations..."

# Compile Named Pipes implementations
gcc -o server_pipe server_pipe.c
if [ $? -eq 0 ]; then
    echo "Named Pipes server compiled successfully!"
else
    echo "Error compiling server_pipe.c"
    exit 1
fi

gcc -o client_pipe client_pipe.c
if [ $? -eq 0 ]; then
    echo "Named Pipes client compiled successfully!"
else
    echo "Error compiling client_pipe.c"
    exit 1
fi

# Compile Sockets implementations
gcc -o server_socket server_socket.c
if [ $? -eq 0 ]; then
    echo "Sockets server compiled successfully!"
else
    echo "Error compiling server_socket.c"
    exit 1
fi

gcc -o client_socket client_socket.c
if [ $? -eq 0 ]; then
    echo "Sockets client compiled successfully!"
else
    echo "Error compiling client_socket.c"
    exit 1
fi

# Compile Shared Memory implementations
gcc -o server_shm server_shm.c
if [ $? -eq 0 ]; then
    echo "Shared Memory server compiled successfully!"
else
    echo "Error compiling server_shm.c"
    exit 1
fi

gcc -o client_shm client_shm.c
if [ $? -eq 0 ]; then
    echo "Shared Memory client compiled successfully!"
else
    echo "Error compiling client_shm.c"
    exit 1
fi

# Compile Semaphores implementations
gcc -o server_sem server_sem.c
if [ $? -eq 0 ]; then
    echo "Semaphores server compiled successfully!"
else
    echo "Error compiling server_sem.c"
    exit 1
fi

gcc -o client_sem client_sem.c
if [ $? -eq 0 ]; then
    echo "Semaphores client compiled successfully!"
else
    echo "Error compiling client_sem.c"
    exit 1
fi

# Compile Signals implementations
gcc -o server_signal server_signal.c
if [ $? -eq 0 ]; then
    echo "Signals server compiled successfully!"
else
    echo "Error compiling server_signal.c"
    exit 1
fi

gcc -o client_signal client_signal.c
if [ $? -eq 0 ]; then
    echo "Signals client compiled successfully!"
else
    echo "Error compiling client_signal.c"
    exit 1
fi

echo "All compilations completed successfully!"
echo ""
echo "Available executables:"
echo "  - Named Pipes: server_pipe, client_pipe"
echo "  - Sockets: server_socket, client_socket"
echo "  - Shared Memory: server_shm, client_shm"
echo "  - Semaphores: server_sem, client_sem"
echo "  - Signals: server_signal, client_signal"