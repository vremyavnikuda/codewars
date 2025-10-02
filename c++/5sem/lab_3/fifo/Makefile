CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGETS = server_pipe client_pipe server_socket client_socket server_shm client_shm server_sem client_sem server_signal client_signal

all: $(TARGETS)

# Named Pipes
server_pipe: server_pipe.c
	$(CC) $(CFLAGS) -o server_pipe server_pipe.c

client_pipe: client_pipe.c
	$(CC) $(CFLAGS) -o client_pipe client_pipe.c

# Sockets
server_socket: server_socket.c
	$(CC) $(CFLAGS) -o server_socket server_socket.c

client_socket: client_socket.c
	$(CC) $(CFLAGS) -o client_socket client_socket.c

# Shared Memory
server_shm: server_shm.c
	$(CC) $(CFLAGS) -o server_shm server_shm.c

client_shm: client_shm.c
	$(CC) $(CFLAGS) -o client_shm client_shm.c

# Semaphores
server_sem: server_sem.c
	$(CC) $(CFLAGS) -o server_sem server_sem.c

client_sem: client_sem.c
	$(CC) $(CFLAGS) -o client_sem client_sem.c

# Signals
server_signal: server_signal.c
	$(CC) $(CFLAGS) -o server_signal server_signal.c

client_signal: client_signal.c
	$(CC) $(CFLAGS) -o client_signal client_signal.c

clean:
	rm -f $(TARGETS)
	rm -f /tmp/tree_fifo_new
	rm -f /tmp/tree_socket

# Test targets for each IPC method
test_pipe: server_pipe client_pipe
	@echo "Testing Named Pipes IPC..."
	@./server_pipe &
	@sleep 2
	@./client_pipe 2
	@sleep 1
	@echo "Named Pipes test completed!"

test_socket: server_socket client_socket
	@echo "Testing Sockets IPC..."
	@./server_socket &
	@sleep 2
	@./client_socket 2
	@sleep 1
	@echo "Sockets test completed!"

test_shm: server_shm client_shm
	@echo "Testing Shared Memory IPC..."
	@./server_shm &
	@sleep 2
	@./client_shm 2
	@sleep 1
	@echo "Shared Memory test completed!"

test_sem: server_sem client_sem
	@echo "Testing Semaphores IPC..."
	@./server_sem &
	@sleep 2
	@./client_sem 2
	@sleep 1
	@echo "Semaphores test completed!"

# Note: Signal test requires PID passing which is complex in make
test_signal: server_signal client_signal
	@echo "Testing Signals IPC..."
	@echo "Note: Signal implementation requires server PID as argument"
	@echo "Please run manually: ./server_signal & and then ./client_signal 2 <PID>"

# Run all tests
test_all: test_pipe test_socket test_shm test_sem

.PHONY: all clean test_pipe test_socket test_shm test_sem test_signal test_all
