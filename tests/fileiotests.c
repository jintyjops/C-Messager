#include <string.h>

#include "headers/fileiotests.h"

#include "../src/headers/fileio.h"

/* Returns 1 on success, 0 on failure, sets errormsg to
useful error message.
Assumes errormsg has been allocated 256 chars of space.*/
int fio_tests(char* errormsg){
    // XXX this is not an exhaustive test!
    char* str;
    if(fio_create(TESTFILE) == 0){
        strcpy(errormsg, "Could not create file.");
        return 0;
    }
    if(fio_write(TESTFILE, TESTSTR) == 0){
        strcpy(errormsg, "Could not write to file.");
        return 0;
    }
    if(fio_read(TESTFILE, &str, 8) == 0){
        strcpy(errormsg, "Could not read from file.");
        return 0;
    }
    if(strcmp(str, TESTSTR) != 0){
        strcpy(errormsg, "Data read from file not the same as data written to file.");
        return 0;
    }
    if(fio_delete(TESTFILE) == 0){
        strcpy(errormsg, "Could not delete file.");
        return 0;
    }
    return 1;
}
