CC=gcc
CFLAGS=-I.

make: server.c client.c socket.c
	$(CC) -o server server.c
	$(CC) -o client client.c
	$(CC) -o socket socket.c

clean:
	rm server socket client
