/* Module for getting input and displaying output to user
Created 09/02/17
Prefix for this module is uio*/
#include <stdio.h>
#include <stdlib.h>

#include "headers/userio.h"
#include "headers/definitions.h"


// This is possible because user input is usually around the same size.
#define BUFFER_SIZE 8

static void copy_buffer(char* data, char* buffer);
static int fill_buffer(char* buffer);

/* Reads an input from the user, blocks until input is read or error occurs.
Sets data to  user input and returns TRUE if successful and FALSE on failure.
Max length is the maximum length the user input can be before the function
returns, -1 for unlimited length. */
int uio_read(char** data, int max_len){

}

/* Fills buffer from stdin */
static int fill_buffer(char* buffer){

}

/* Copies buffer to data, assumes data has enough space */
static void copy_buffer(char* data, char* buffer){

}
