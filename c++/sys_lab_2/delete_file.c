#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    // Use the unlink system call to delete the file
    if (unlink(filename) == -1) {
        perror("Error deleting file");
        return 1;
    }

    printf("File '%s' deleted successfully\n", filename);
    return 0;
}