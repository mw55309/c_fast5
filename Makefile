CC=gcc
CFLAGS=-I/usr/include -Wall -Wextra
LDFLAGS=-L/usr/lib/i386-linux-gnu/ -lhdf5

f5: f5.c
	$(CC) $(CFLAGS) f5.c $(LDFLAGS) -o f5

fast5extract: fast5extract.c
	$(CC) $(CFLAGS) fast5extract.c $(LDFLAGS) -o fast5extract

clean:
	rm f5

.PHONY:
	clean

