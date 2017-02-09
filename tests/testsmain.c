/* Unit test for messager */
#include <stdlib.h>
#include <stdio.h>

#include "headers/fileiotests.h"

void iotests(char* errormsg);

int main(){
    char* errormsg = malloc(256 * sizeof(char));

    iotests(errormsg);

    free(errormsg);
    return 0;
}

/* tests for fileio.c, networkio.c, and userio.c */
void iotests(char* errormsg){
    if(fio_tests(errormsg) == 0){
        printf("%s\n", errormsg);
    }else{printf("File IO tests success.");}
}
