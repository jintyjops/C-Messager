#ifndef USERIO
#define USERIO

#include <pthread.h>

// Defined here so that other modules can use it.
pthread_mutex_t display_lock;

int uio_init();
int uio_read(char** data, char* prompt, int max_len);
void uio_display(char* data);
void uio_display_nn(char* data);

#endif
