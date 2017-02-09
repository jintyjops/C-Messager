#include <string.h>
#include <stdio.h>

#include "headers/fileiotests.h"

#include "../src/headers/fileio.h"

/* Returns 1 on success, 0 on failure, sets errormsg to
useful error message.
Assumes errormsg has been allocated 256 chars of space.*/
int fio_tests(char* errormsg){
    // XXX this is not an exhaustive test!
    char* str;
    int result = 1;
    if(fio_create(TESTFILE) == 0){
        strcpy(errormsg, "Could not create file.");
        result = 0;
    }
    if(fio_write(TESTFILE, TESTSTR) == 0){
        strcpy(errormsg, "Could not write to file.");
        result = 0;
    }
    if(fio_is_file(TESTFILE) == 0){
        strcpy(errormsg, "Could not test for file validity.");
        result = 0;
    }
    if(fio_read(TESTFILE, &str, 8) == 0){
        strcpy(errormsg, "Could not read from file.");
        result = 0;
    }
    if(strcmp(str, TESTSTR) != 0){
        strcpy(errormsg, "Data read from file not the same as data"
        "written to file.");
        result = 0;
    }
    if(fio_delete(TESTFILE) == 0){
        strcpy(errormsg, "Could not delete file.");
        result = 0;
    }
    return result;
}
