CC = gcc
CFLAGS = -Wall -Werror -I/usr/include/nghttp2
LDFLAGS = -I/usr/include/nghttp2

all: main_curl

main_curl: main_curl.o
	$(CC) -o $@ $^ $(LDFLAGS)

main_curl.o: main_curl.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main_curl main_curl.o
