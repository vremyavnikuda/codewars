# Linux System Calls Demonstration

This project demonstrates interaction between bash and C programs using system calls in Linux OS.

## Programs Included

### C Programs
1. `hello_world.c` - Simple "Hello World!" program
2. `help_program.c` - Prints program description
3. `create_file.c` - Creates a file with specified content using system calls
4. `delete_file.c` - Deletes a file using system calls
5. `read_hash_file.c` - Reads file content and calculates hash value

### Bash Programs
1. `menu.sh` - Interactive menu for file operations
2. `compile.sh` - Script to compile all C programs

## Compilation and Execution

To compile the programs, run the following command on a Linux system (or WSL):

```bash
chmod +x compile.sh
./compile.sh
```

To run the interactive menu:

```bash
chmod +x menu.sh
./menu.sh
```

## System Calls Used

The C programs use the following Linux system calls:
- `open()` - To create/open files
- `read()` - To read file content
- `write()` - To write file content
- `unlink()` - To delete files
- `close()` - To close file descriptors

## Operations Available

1. Display program description
2. Create a file with specified content
3. Delete a specified file
4. Read file content and calculate hash value
5. Show operation statistics

## Notes

- These programs use Linux-specific system calls and are intended to run on a Linux system or WSL.
- The bash script tracks successful and failed operations and displays statistics.
- Hash calculation uses the djb2 algorithm for demonstration purposes.