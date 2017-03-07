CC=gcc
PROGRAM = bin/messager.exe
# Source files go here.
SRCS = src/main.c src/mainloop.c src/fileio.c src/userio.c src/networkio.c

$(PROGRAM) : $(SRCS)
	$(CC) $(SRCS) -o $(PROGRAM)

run:
	$(PROGRAM) -g
