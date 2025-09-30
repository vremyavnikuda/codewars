# Interaction Test Results and Instructions

## Programs Created:

1. `hello_world.c` - Basic "Hello World" program in C
2. `help_program.c` - Displays program description
3. `create_file.c` - Creates a file with specified content
4. `delete_file.c` - Deletes a specified file
5. `menu.sh` - Interactive bash script with menu and statistics

## To Run on Linux:

1. Make the bash script executable:
   ```bash
   chmod +x menu.sh
   ```

2. Compile all C programs:
   ```bash
   gcc hello_world.c -o hello_world
   gcc help_program.c -o help_program
   gcc create_file.c -o create_file
   gcc delete_file.c -o delete_file
   ```

3. Run the main menu script:
   ```bash
   ./menu.sh
   ```

## System Call Interaction Notes:

The programs demonstrate interaction between bash and C in a Linux environment:
- The bash script calls C executables using system calls
- Exit codes are checked to determine success/failure
- Statistics are tracked for successful and failed operations
- The C programs use standard library functions that interface with system calls (fopen, remove, etc.)

## Expected Behavior:
- Menu displays with options 1-5
- Each operation calls a corresponding C program
- Statistics are updated based on C program exit codes
- Final statistics are shown on exit