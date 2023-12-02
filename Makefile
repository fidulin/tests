CC = gcc
CFLAGS = -Wall -Wextra

all: testing

testing: testing.c
	$(CC) $(CFLAGS) -o testing testing.c

clean:
	rm -f testing
