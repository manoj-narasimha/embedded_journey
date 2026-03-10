CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
TARGET = bit_toolkit
SRCS   = main.c converter.c bit_tools.c
OBJS   = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✅ Build complete → $(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe 2>NUL || true