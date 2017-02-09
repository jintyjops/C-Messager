#ifndef FILEIO

int fio_read(char* filename, char** data, int buffer_size);
int fio_is_file(char* file);
int fio_create(char* filename);

#endif
