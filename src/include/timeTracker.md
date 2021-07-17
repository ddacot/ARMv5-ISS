# Header

Name: Gabriel Cojocaru
Course Number: 310
Submission Date: 9/8
Hours Spent: 20

# Overview:

In this assignment, I had to create a software that would load an ELF file, generated for the ARM platform, into my simulator. The program receives arguments from the command line, then starts the program with the setting specified by arguments. The software also performs unit tests on various functions that interact with the memory and with the ELF file.

# Prerequisites:

The software runs on Windows 10. My proram is a standalone program, so it does not require and environment to run, except a few dll's.


# Build and Test:

To compile the project, open the *.pro file with Qt Designer. Then go to Projects -> choose MinGW compiler, then under Run, specify the command line arguments (ex --load test2.exe  --mem 32768). To perform the unit tests, append to the argument lists either "--test" or "-t" flag.

# Configuration:

To turn the logging on/off, include the flag "--log" to the command line arguments list.
To specify the memory size, include the flag "--mem \<size>" - where \<size> is the size in bytes fo the memory.
To specify the ELF file name, include the flag "--load \<filename>" - where \<filename> is the name of the elf file. (has to be in the same directory as the executable)

# User Guide:

To run the program, open Command Prompt. Navigate to the directory where the executable is built. (cd \<dir>). Then run the program with: armsim --mem \<memsize> --load \<filename> (and other flags).

# Bug Report

1. The logging framework I am using, does not support file redirect, therefore my program does not support yet file redirection.

# Academic Integrity Statement

By affixing my signature below, I certify that the accompanying work represents my own intellectual effort. Furthermore, I have received no outside help other than what is documented below.

| 9/7 | AJ Steenhoek | Question about bug in the ifstream class | 10 minutes |