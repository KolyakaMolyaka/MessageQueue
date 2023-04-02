CC=gcc
CFLAGS=-c 
WFLAGS=-Wall
GENERATE_MESSAGES_EXECUTABLE=generate_messages.exe
RECEIVE_MESSAGES_EXECUTABLE=receive_messages.exe

all: msglib.o generate_messages.o receive_messages.o
	$(CC) $(WFLAGS) msglib.o generate_messages.o  -o $(GENERATE_MESSAGES_EXECUTABLE) 
	$(CC) $(WFLAGS) msglib.o receive_messages.o -o $(RECEIVE_MESSAGES_EXECUTABLE) 
	rm *.o

msglib.o: src/msglib.c
	$(CC) $(CFLAGS) $(WFLAGS) src/msglib.c

generate_messages.o: src/generate_messages.c
	$(CC) $(CFLAGS) $(WFLAGS) src/generate_messages.c

receive_messages.o: src/receive_messages.c 
	$(CC) $(CFLAGS) $(WFLAGS) src/receive_messages.c 

clean:
	rm *.exe


