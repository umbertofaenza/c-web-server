# COMPILER
CC = gcc # Compiler
CFLAGS = -Wall -Wextra -g # Compiler Flags

# FILES
TARGET = server # Final executable file
OBJS = main.o http_handler.o custom_routing.o # Object files

# MAIN RULE
all: $(TARGET)

# LINKING
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# COMPILING
# main.c
main.o: main.c http_handler.h custom_routing.h
	$(CC) $(CFLAGS) -c main.c

# http_handler.c
http_handler.o: http_handler.c http_handler.h custom_routing.h
	$(CC) $(CFLAGS) -c http_handler.c

# custom_routing.c
custom_routing.o: custom_routing.c custom_routing.h
	$(CC) $(CFLAGS) -c custom_routing.c

# CLEANING
clean:
	rm -f $(OBJS) $(TARGET)