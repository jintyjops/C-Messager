CC=gcc
PROGRAM = bin/messager.exe
SRCS = src/main.c

$(PROGRAM) : $(SRCS)
	$(CC) $(SRCS) -o $(PROGRAM)

run:
	$(PROGRAM)
