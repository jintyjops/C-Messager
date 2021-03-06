/* Module for getting input and displaying output to user
Created 09/02/17
Prefix for this module is uio*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "headers/userio.h"
#include "headers/fileio.h"
#include "headers/definitions.h"


// This is possible because user input is usually around the same size.
#define UIO_BUFFER_SIZE 8

/* Initialises user io, return TRUE on success, FALSE on failure. */
int uio_init(){
    if(pthread_mutex_init(&display_lock, NULL) != 0){
        return FALSE;
    }
    return TRUE;
}

/* Reads an input from the user, blocks until input is read or error occurs.
Sets data to  user input and returns TRUE if successful and FALSE on failure.
Max length is the maximum length the user input can be before the function
returns, -1 for unlimited length. */
int uio_read(char** data, char* prompt, int max_len){
    int index = 0;
    char chr;
    *data = malloc(sizeof(char));

    if(max_len == -1){
        max_len = INT_MAX;
    }

    uio_display_nn(prompt);

    while((chr = fgetc(stdin)) != EOF && chr != '\n' && index + 1 < max_len){
        // XXX: implement a buffer system for this.
        // Plus two to give space for null at the end.
        *data = realloc(*data, (index + 2) * sizeof(char));
        (*data)[index] = chr;
        index++;
    }
    (*data)[index] = '\0';

    return TRUE;
}

/* Displays some string to the user with a newline automatically added,
assumes uio_init() has been successfully called */
void uio_display(char* data){
    int len = strlen(data) + 2;
    char* strnewline = malloc(len * sizeof(char));
    strcpy(strnewline, data);
    // This should overwrite the NULL terminator from data.
    strnewline[len - 2] = '\n';
    strnewline[len - 1] = '\0';
    uio_display_nn(strnewline);
}

/* Displays some string to the user without a newline, assumes uio_init() has been
successfully called. */
void uio_display_nn(char* data){
    pthread_mutex_lock(&display_lock);
    // Implementation of display here can change.
    printf("%s", data);
    pthread_mutex_unlock(&display_lock);
}
