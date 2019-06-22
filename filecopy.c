#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//You may also add more include directives as well.

// THIS VALUE CANNOT BE CHANGED.
// You should use this value when creating your buffer.
// And also to limit the amount of bytes each read CAN do.
#define BUFF_MAX 13
// ABOVE VALUE CANNOT BE CHANGED //



int main(int argc, char const *argv[]) {
    ssize_t readInputFrom;
    int openInputFrom, openOutputTo, byteCount;
    char inputFrom[50], outputTo[50], readBuffer[BUFF_MAX];
    
    // Greet
    printf("Welcome to the File Copy Program by Jonathon Knack!\n");
    
    // Acquire input file name
    // Write prompt to screen
    printf("Enter the name of the file to copy from:\n");
    // Accept input
    scanf("%s", inputFrom);
    // Open the input file
    openInputFrom = open(inputFrom, O_RDONLY);
    // If file doesn't exist, abort
    if(openInputFrom == -1) {   // If the file doesn't exist open returns -1
        perror("ERROR:");
        close(openInputFrom);
        return 1;
    }
    
    // Acquire output file name
    // Write prompt to screen
    printf("Enter the name of the file to copy to:\n");
    // Accept input
    scanf("%s", outputTo);

    // Check if we are reading and writing to the same file
    if(strcmp(inputFrom,outputTo) != 0) {
        // Create output file
        openOutputTo = open(outputTo, O_WRONLY | O_CREAT | O_EXCL);
        if(openOutputTo == -1) {
            // If you can't create a new file open the existing file and truncate it
            openOutputTo = open(outputTo, O_WRONLY | O_TRUNC);
        }

        // Loop
        // Read from input file
        // Until read fails

        while((readInputFrom = read(openInputFrom, readBuffer, BUFF_MAX)) > 0) {
            // Write to output file
            write(openOutputTo, readBuffer, readInputFrom);
            byteCount += readInputFrom;
        }
    // This is reading and writing to the same file
    } else {
        // open new temp file to write contents to
        openOutputTo = open("tempOutput", O_WRONLY | O_CREAT | O_EXCL);
        
        // Loop
        // Read from input file
        // Until read fails
        // Write to temporary file 
        while((readInputFrom = read(openInputFrom, readBuffer, BUFF_MAX)) > 0) {
            // Write to output file
            write(openOutputTo, readBuffer, readInputFrom);
            byteCount += readInputFrom;
        }

        // Delete the temporary file
        remove(inputFrom);
        
        // Rename temp file
        rename("tempOutput", inputFrom);
       
        
        
    }

    // Close output file
    close(openInputFrom);
    close(openOutputTo);
    
    // Write completion message to screen
    printf("File Copy Successful, %d bytes copied\n", byteCount);
    
    // Terminate normally
    return 0;
}