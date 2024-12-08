# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Target name and source files
TARGET = detectCycles
SRCS = main.c Graph.c LinkedList.c cycleDetection.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Link the object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
