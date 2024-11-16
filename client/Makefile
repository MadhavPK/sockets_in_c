# 2024-11-16 14:58:17
# 					Client
#

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinc -g

# static linking
STATIC = -static

# Linking libs
LIBS = -lws2_32 -liphlpapi

# Source and object files
SRCDIR = src
INCDIR = inc
OBJDIR = obj

# Target executable
TARGET = $(OBJDIR)/client.exe

# List all .c files in src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Convert source files to object files in obj directory
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target: Build the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(STATIC) $(LIBS)

# Rule to build object files from .c files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove build files
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
