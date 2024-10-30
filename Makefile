# Makefile for myshell project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRCS = myshell.c argparse.c builtin.c

# Object files
OBJS = myshell.o argparse.o builtin.o

# Target executable
TARGET = myshell

# Default target: build myshell
default: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile source files into object files
myshell.o: myshell.c argparse.h builtin.h
	$(CC) $(CFLAGS) -c myshell.c

argparse.o: argparse.c argparse.h
	$(CC) $(CFLAGS) -c argparse.c

builtin.o: builtin.c builtin.h
	$(CC) $(CFLAGS) -c builtin.c

# Debug target: build myshell with debug flags
debug: CFLAGS += -O0 -ggdb
debug: $(TARGET)

# Clean target: delete object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

