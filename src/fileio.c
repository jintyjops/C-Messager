
/* General file input and output
All fucntions to be used externally use the fio extension.
Created 9/2/17 */

// XXX These functions are completely untested / incomplete!

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers/fileio.h"
#include "headers/definitions.h"

static int fill_buffer(FILE* fp, char* buffer, int buffer_size);
static void copy_buffer(char* dest, char* src, int size);

/* Reads entire file into memory, data is data read from a file, buffer is the
file buffer to void to many calls to realloc.
Returns TRUE if file read ok and FALSE if there was an error.
Assumes file already exists.*/
int fio_read(char* filename, char** data, int buffer_size){
    char* buffer;
    int strindex, buff_return;
    FILE* fp;

    strindex = 0;
    *data = malloc(sizeof(char));
    buffer = malloc(buffer_size * sizeof(char));

    fp = fopen(filename, "r");

    if(fp == NULL){
        return 0;
    }

    while((buff_return = fill_buffer(fp, buffer, buffer_size)) != EOF){
        *data = realloc(*data, (strindex + buff_return - 1) * sizeof(char));
        // Copy characters from buffer to data.
        copy_buffer(&(*data)[strindex], buffer, buff_return);
        strindex += buff_return - 1;
    }

    (*data)[strindex] = '\0';
    fclose(fp);
    return 1;
}

static void copy_buffer(char* dest, char* src, int size){
    int i;
    for(i = 0; i < size; i++){
        dest[i] = src[i];
    }
}

/* Files a buffer from the file an returns the amount filled.
Returns EOF on if no characters read or error. */
static int fill_buffer(FILE* fp, char* buffer, int buffer_size){
    int index = 0;
    char chr;

    while(index < buffer_size && (chr = fgetc(fp)) != EOF){
        buffer[index] = chr;
        ++index;
    }

    if(index == 0){
        return EOF;
    }
    return index + 1;
}

/* Returns TRUE if file exists, FALSE if not */
int fio_is_file(char* file){
    if(access(file, F_OK) != -1){
        return TRUE;
    }
    return FALSE;
}

/* Creates a file, returns TRUE on success, FALSE on failure.*/
int fio_create(char* filename){
    FILE* fp;
    if((fp = fopen(filename, "w")) != NULL){
        fclose(fp);
        return TRUE;
    }
    return FALSE;
}

/* Deletes a file, returns TRUE on success, FALSE on failure. */
int fio_delete(char* filename){
    if(remove(filename) == 0){
        return TRUE;
    }
    return FALSE;
}

/* Write string to file, returns TRUE on success, FALSE on failure. */
int fio_write(char* filename, char* data){
    FILE* fp = fopen(filename, "w");
    if(fp == NULL){
        return FALSE;
    }

    fprintf(fp, data);
    fclose(fp);

    return TRUE;
}
