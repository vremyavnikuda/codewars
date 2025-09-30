#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Simple hash function (djb2 algorithm)
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int fd;
    char buffer[1024];
    ssize_t bytes_read;
    char *content = NULL;
    size_t total_size = 0;
    size_t allocated_size = 0;

    // Use the open system call to open the file
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Read file content using the read system call
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Resize content buffer if necessary
        if (total_size + bytes_read >= allocated_size) {
            allocated_size = allocated_size == 0 ? 1024 : allocated_size * 2;
            content = realloc(content, allocated_size);
            if (content == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                close(fd);
                return 1;
            }
        }
        
        memcpy(content + total_size, buffer, bytes_read);
        total_size += bytes_read;
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        free(content);
        close(fd);
        return 1;
    }

    close(fd);

    if (content != NULL) {
        // Add null terminator
        if (total_size + 1 >= allocated_size) {
            content = realloc(content, total_size + 1);
        }
        content[total_size] = '\0';

        // Calculate hash
        unsigned long file_hash = hash((unsigned char*)content);

        // Output filename and hash value
        printf("Filename: %s\n", filename);
        printf("Hash: %lu\n", file_hash);
        printf("Content:\n%s\n", content);

        free(content);
    } else {
        // File is empty
        unsigned long empty_hash = hash((unsigned char*)"");
        printf("Filename: %s\n", filename);
        printf("Hash: %lu\n", empty_hash);
        printf("Content: (empty file)\n");
    }

    return 0;
}