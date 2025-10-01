#!/bin/bash

# Menu script to run different IPC method implementations

# Function to compile a program
compile_program() {
    local src=$1
    local target=$2
    if [ ! -f "$src" ]; then
        echo "Source file $src not found!"
        return 1
    fi
    gcc -o "$target" "$src"
    if [ $? -ne 0 ]; then
        echo "Failed to compile $src"
        return 1
    fi
    return 0
}

# Function to check if executables exist
check_executables() {
    local server_exe=$1
    local client_exe=$2
    if [ ! -f "./$server_exe" ] || [ ! -f "./$client_exe" ]; then
        echo "Compiling $server_exe and $client_exe..."
        compile_program "$server_exe.c" "$server_exe" || return 1
        compile_program "$client_exe.c" "$client_exe" || return 1
    fi
    return 0
}

while true; do
    clear
    echo "=========================================="
    echo "         IPC Methods Menu"
    echo "=========================================="
    echo "1. Signals"
    echo "2. Shared Memory"
    echo "3. Semaphores"
    echo "4. Sockets"
    echo "5. Named/Unnamed Pipes"
    echo "6. Exit"
    echo "=========================================="
    read -p "Enter your choice [1-6]: " choice

    case $choice in
        1)
            # Signals implementation
            clear
            echo "=========================================="
            echo "         Running Signals Demo"
            echo "=========================================="
            echo "Signals are used for inter-process communication."
            echo "However, they are not ideal for transferring large amounts of data."
            echo "The implementation here uses signals for synchronization and"
            echo "a shared global buffer for data (which is not actually safe with signals)."
            echo ""
            echo "Starting server (Signals)..."
            ./server_signal &
            SERVER_PID=$!
            sleep 2
            echo ""
            echo "Starting client (Signals) - requires server PID as parameter..."
            if check_executables "server_signal" "client_signal"; then
                ./client_signal 3 $SERVER_PID
            fi
            read -p "Press Enter to continue..."
            ;;
        2)
            # Shared Memory implementation
            clear
            echo "=========================================="
            echo "      Running Shared Memory Demo"
            echo "=========================================="
            echo "Shared memory allows multiple processes to access the same memory segment."
            echo "It provides very fast communication between processes."
            echo ""
            echo "Starting server (Shared Memory)..."
            if check_executables "server_shm" "client_shm"; then
                ./server_shm &
                SERVER_PID=$!
                sleep 2
                echo ""
                echo "Starting client (Shared Memory)..."
                ./client_shm
                # Kill server if still running
                kill -9 $SERVER_PID 2>/dev/null
            fi
            read -p "Press Enter to continue..."
            ;;
        3)
            # Semaphores implementation
            clear
            echo "=========================================="
            echo "        Running Semaphores Demo"
            echo "=========================================="
            echo "Semaphores are used to control access to shared resources."
            echo "They work in conjunction with shared memory for process synchronization."
            echo ""
            echo "Starting server (Semaphores)..."
            if check_executables "server_sem" "client_sem"; then
                ./server_sem &
                SERVER_PID=$!
                sleep 2
                echo ""
                echo "Starting client (Semaphores)..."
                ./client_sem
                # Kill server if still running
                kill -9 $SERVER_PID 2>/dev/null
            fi
            read -p "Press Enter to continue..."
            ;;
        4)
            # Sockets implementation
            clear
            echo "=========================================="
            echo "         Running Sockets Demo"
            echo "=========================================="
            echo "Sockets provide bidirectional communication between processes."
            echo "This implementation uses UNIX domain sockets for local IPC."
            echo ""
            echo "Starting server (Sockets)..."
            if check_executables "server_socket" "client_socket"; then
                ./server_socket &
                SERVER_PID=$!
                sleep 2
                echo ""
                echo "Starting client (Sockets)..."
                ./client_socket
                # Kill server if still running
                kill -9 $SERVER_PID 2>/dev/null
            fi
            read -p "Press Enter to continue..."
            ;;
        5)
            # Named Pipes implementation
            clear
            echo "=========================================="
            echo "      Running Named Pipes Demo"
            echo "=========================================="
            echo "Named pipes (FIFOs) provide unidirectional communication."
            echo "Data written by one process can be read by another through a file."
            echo ""
            echo "Starting server (Named Pipes)..."
            if check_executables "server_pipe" "client_pipe"; then
                ./server_pipe &
                SERVER_PID=$!
                sleep 2
                echo ""
                echo "Starting client (Named Pipes)..."
                ./client_pipe
                # Kill server if still running
                kill -9 $SERVER_PID 2>/dev/null
            fi
            read -p "Press Enter to continue..."
            ;;
        6)
            echo "Exiting program..."
            break
            ;;
        *)
            echo "Invalid option. Please enter a number between 1-6."
            sleep 2
            ;;
    esac
done