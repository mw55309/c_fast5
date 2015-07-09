CC=gcc
CFLAGS=-I/usr/include -Wall -Wextra
LDFLAGS=-L/usr/lib/i386-linux-gnu/ -lhdf5

f5: f5.c
	$(CC) $(CFLAGS) f5.c $(LDFLAGS) -o f5

clean:
	rm f5

.PHONY:
	clean
