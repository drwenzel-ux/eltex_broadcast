.PHONY: all clean

all: server

server: server.c
	cc -g -o $@ $<

clean:
	rm -f server