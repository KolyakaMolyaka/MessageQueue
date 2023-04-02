all:
	gcc src/generate_messages.c src/msglib.c -o generate_messages.exe
	gcc src/receive_messages.c src/msglib.c -o receive_messages.exe
