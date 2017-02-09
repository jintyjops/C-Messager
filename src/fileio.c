
/* General file input and output
All fucntions to be used externally use the fio extension.
Created 9/2/17 */

// XXX These functions are completely untested / incomplete!

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/fileio.h"
#include "headers/definitions.h"

int fill_buffer(FILE* fp, char** buffer, int buffer_size);

/* Reads entire file into memory, data is data read from a file, buffer is the
file buffer to void to many calls to realloc.
Returns 1 if file read ok and 0 if there was an error.
Assumes file already exists.*/
int fio_get(char* filename, char** data, int buffer_size){
    char* buffer;
    int str_len, buff_return, i;
    FILE* fp;

    str_len = 1;
    *data = malloc(str_len * sizeof(char));
    buffer = malloc(buffer_size * sizeof(char));

    fp = fopen(filename, "r");

    while((buff_return = fill_buffer(fp, &buffer, buffer_size)) != 0){
        str_len += buff_return;
        *data = realloc(*data, str_len * sizeof(char));
        for(i = str_len - buff_return; i < str_len; i++){
            (*data)[i] = buffer[i - (str_len - buff_return)];
        }
    }

    return 1;
}

/* Files a buffer from the file an returns the amount filled. */
int fill_buffer(FILE* fp, char** buffer, int buffer_size){
    int len = 0;
    char chr;

    while(len + 1 != buffer_size && (chr = fgetc(fp)) != '\0'){
        ++len;
        (*buffer)[len - 1] = chr;
    }

    return len;
}

/* Returns 1 if file exists, 0 if not */
int fio_is_file(char* file){
    if(access(file, F_OK) != -1){
        return TRUE;
    }
    return FALSE;
}

/* */
int fio_create(char* filename){
    return 0;
}
