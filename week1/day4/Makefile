# Compiler settings
CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic

# Target
TARGET  = firmware_sim

# Source files
SRCS    = main.c gpio_driver.c uart_driver.c sensor.c

# Object files (replace .c with .o)
OBJS    = $(SRCS:.c=.o)

# Default target — build everything
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✅ Build successful → $(TARGET)"

# Compile each .c file into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	del /Q *.o $(TARGET).exe 2>NUL || true

# Show build info
info:
	@echo "Sources : $(SRCS)"
	@echo "Objects : $(OBJS)"
	@echo "Target  : $(TARGET)"