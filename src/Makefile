CC = gcc
CFLAGS = -Wall -Werror -lcurl 
CURLFLAG= -g
LDFLAGS = -lcurl
all:  main_curl


main_curl: main_curl.o
	$(CC) -o $@ $^ $(LDFLAGS)

main_curl.o: main_curl.c
	$(CC) $(CFLAGS) $(CURLFLAG) $(LDFLAGS) -c $<



clean:
	rm -f main_curl main_curl.o
