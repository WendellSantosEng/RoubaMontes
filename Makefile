CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = tst

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXECUTABLE)
