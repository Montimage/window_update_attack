CC = gcc
CFLAGS = -Wall -Werror -lcurl
LDFLAGS = -lcurl

all: main_curl

main_curl: main_curl.o
	$(CC) -o $@ $^ $(LDFLAGS)

main_curl.o: main_curl.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f main_curl main_curl.o
