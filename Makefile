CC = gcc
CFLAGS = -Wall -Wextra

all: shell

shell: src/main.c src/filesystem.c
	$(CC) $(CFLAGS) -o bin/ext4shell src/main.c src/filesystem.c

clean:
	rm -f bin/shell
