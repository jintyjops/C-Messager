CC=gcc
PROGRAM = bin/messager.exe
# Source files go here.
SRCS = src/main.c

$(PROGRAM) : $(SRCS)
	$(CC) $(SRCS) -o $(PROGRAM)

run:
	$(PROGRAM)
