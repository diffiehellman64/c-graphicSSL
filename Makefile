CC=gcc
CFLAGS=-Wall -ggdb -O2

BJS= main.o
BINARY=c-graphicSSL

all: $(BINARY)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *~ $(BINARY)
