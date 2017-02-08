CC=gcc
PROGRAM=interpreter.exe
SRCS = src/main.c

$(PROGRAM) : $(SRCS)
	$(CC) $(SRCS) -o $(PROGRAM)

run:
	$(PROGRAM)
