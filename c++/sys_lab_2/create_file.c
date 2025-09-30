#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // Check if correct number of arguments provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <content>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *content = argv[2];
    int fd;

    // Use the open system call to create the file
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    if (fd == -1) {
        perror("Error creating file");
        return 1;
    }

    // Use the write system call to write content to the file
    ssize_t bytes_written = write(fd, content, strlen(content));
    
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);

    printf("File '%s' created successfully with content: %s\n", filename, content);
    return 0;
}