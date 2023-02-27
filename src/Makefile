CC = gcc
CFLAGS = -Wall -Werror -lcurl -pthread
CURLFLAG= -g
LDFLAGS = -lcurl -pthread
all:  main_curl


main_curl: main_curl.o
	$(CC) -o $@ $^ $(LDFLAGS)

main_curl.o: main_curl.c
	$(CC) $(CFLAGS) $(CURLFLAG) $(LDFLAGS) -c $<



clean:
	rm -f main_curl main_curl.o