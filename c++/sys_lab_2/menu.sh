#!/bin/bash

# Initialize statistics
successful_ops=0
failed_ops=0

# Function to show menu
show_menu() {
    echo "=================================="
    echo "        FILE MANAGEMENT MENU      "
    echo "=================================="
    echo "This program demonstrates interaction between bash and C programs"
    echo "using system calls in Linux OS."
    echo ""
    echo "1 - Description of the program (HELP)"
    echo "2 - Create a file"
    echo "3 - Delete a file"
    echo "4 - Read file content and calculate hash"
    echo "5 - Show statistics"
    echo "6 - Exit"
    echo "=================================="
}

# Function to update statistics
update_stats() {
    if [ $1 -eq 0 ]; then
        successful_ops=$((successful_ops + 1))
        echo "Operation completed successfully."
        echo "System call returned: SUCCESS"
    else
        failed_ops=$((failed_ops + 1))
        echo "Operation failed."
        echo "System call returned: ERROR"
    fi
}

# Main loop
while true; do
    show_menu
    read -p "Select an option (1-6): " choice
    
    case $choice in
        1)
            echo "Calling help program (using system call)..."
            ./help_program
            exit_code=$?
            update_stats $exit_code
            ;;
        2)
            read -p "Enter filename: " filename
            read -p "Enter content for the file: " content
            echo "Creating file: $filename with content: $content"
            echo "Making system call to create file..."
            ./create_file "$filename" "$content"
            exit_code=$?
            update_stats $exit_code
            ;;
        3)
            read -p "Enter filename to delete: " filename
            echo "Deleting file: $filename"
            echo "Making system call to delete file..."
            ./delete_file "$filename"
            exit_code=$?
            update_stats $exit_code
            ;;
        4)
            read -p "Enter filename to read: " filename
            echo "Reading file: $filename and calculating hash value"
            echo "Making system call to read file and calculate hash..."
            ./read_hash_file "$filename"
            exit_code=$?
            update_stats $exit_code
            ;;
        5)
            echo "=================================="
            echo "        STATISTICS         "
            echo "=================================="
            echo "Successful operations: $successful_ops"
            echo "Failed operations: $failed_ops"
            echo "Total operations: $((successful_ops + failed_ops))"
            echo "=================================="
            ;;
        6)
            echo "Exiting program..."
            break
            ;;
        *)
            echo "Invalid option. Please select 1-6."
            ;;
    esac
    
    echo ""
    read -p "Press Enter to continue..."
done

echo "=================================="
echo "FINAL STATISTICS:"
echo "Successful operations: $successful_ops"
echo "Failed operations: $failed_ops"
echo "Total operations: $((successful_ops + failed_ops))"
echo "=================================="