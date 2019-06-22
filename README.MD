# CSC 415 - Project 2 - File copy

## Student Name : Jonathon Knack

## Student ID   : 917629133

## Build Instructions
In the terminal type "make"

## Run Instructions
./fc

## strace/dtruss output
CALL                                        COUNT
access                                                1
bsdthread_register                             1
close                                                   1
getentropy                                          1
getpid                                                 1
getrlimit                                               1
issetugid                                             1
proc_info                                             1
stat64                                                  1
sysctlbyname                                      1
csops                                                  2
fstat64                                                 2
read_nocancel                                     2
open                                                    3
write_nocancel                                    3
ioctl                                                     4
mprotect                                             8
write                                              1089
read                                               1090

First the program greets the user welcoming them to the File Copy Program. The program then prompts the user for the name of the file to read from, store it in a character array then using the open() system call to store the value into openInputFrom. The program then checks if there was an error opening the file and if there is we print the error message using perror(), close the file and exit the program returning 1. Then the program asks for the name of the file to write to and we enter our conditional. The strcmp function is used to check if the read file is the same as the write file if they aren't the same we enter the conditional. The program then tries to create a new file based on the output file name if it fails the file opens and is truncated. Using the read() system call we read from the input file until it fails storing what was read in a character array that is the size of the BUFF_MAX. If the input file and the output file are the same we do the same thing as above but we write to a temporary file, we remove the initial file then rename the temporary file with the input file name. Once out of the conditional both files are closed and the user is told the files were copied successfully and how many bytes were copied.



