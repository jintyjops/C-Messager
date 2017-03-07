#ifndef FILEIO
#define FILEIO

#include <stdio.h>

int fio_read(char* filename, char** data, int buffer_size);
int fio_read_file(FILE* fp, char** data, int buffer_size);
int fio_is_file(char* file);
int fio_create(char* filename);
int fio_delete(char* filename);
int fio_write(char* filename, char* data);

#endif
