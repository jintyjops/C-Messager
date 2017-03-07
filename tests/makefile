CC=gcc
PROGRAM = tests.exe
# Source files go here.
SRCS = testsmain.c fileiotests.c ../src/fileio.c useriotests.c ../src/userio.c

$(PROGRAM) : $(SRCS)
	$(CC) $(SRCS) -o $(PROGRAM)

run:
	$(PROGRAM)
