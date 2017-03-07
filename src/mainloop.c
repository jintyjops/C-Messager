#include <pthread.h>
#include <string.h>
#include <stdio.h>

// To include sleep function for windows or unix.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "headers/mainloop.h"
#include "headers/userio.h"

struct program_state state = {
    TRUE,
    FALSE,
};

// User commands.
const char* USER_COMMANDS[NUM_USER_COMMANDS] = {
    "quit",
    "join"
};

// Array of user commands that correspond to indexes of user command above.
Commandptr_t USER_COMMAND_FUNCS[NUM_USER_COMMANDS] = {
    quit_command,
    join_command
};

void start_user_input(){
    uio_init();
    user_io_loop();
}

void start_network(){

}

/* Handles user input */
static int user_io_loop(){
    char** user_input;
    char* args[MAX_ARGS] = {};
    int num_args;
    user_input = malloc(sizeof(char*));

    while(state.program_running){
        free_args(args);
        uio_read(user_input, COMMAND_INPUT_PROMPT, MAX_USER_INPUT);
        strip_whitespace(*user_input);
        num_args = separate_args(args, *user_input);
        parse_user_input(args, num_args);
    }

    uio_display("Shutting down user input...");
}

/* Takes command given by user (separated by words),
then finds and runs command. */
static void parse_user_input(char** args, int num_args){
    int i;
    char* command;

    if(num_args == 0){
        // Don't display anyting.
        return;
    }

    command = args[0];

    for(i = 0; i < NUM_USER_COMMANDS; i++){
        if(strcmp(command, USER_COMMANDS[i]) == 0){
            USER_COMMAND_FUNCS[i](args);
            return;
        }
    }

    // If function gets this far then no command has been run.
    uio_display(NO_COMMAND_SPECIFIED_MESSAGE);
}

/* Separates args out and places them in **args.
Returns the number of args.  */
static int separate_args(char** args, char* input){
    int words = 0, index = -1, last_word_index = 0, i;
    char chr;

    while(TRUE){
        // Go to next word space or end of string.
        while((chr = input[++index]) != ' ' && chr != '\0');

        // Allocate memory for arg (don't need index + 1 as index is already
        // on space after final character).
        args[words] = malloc((index - last_word_index) * sizeof(char));

        // Copy arg from input to args.
        for(i = last_word_index; i < index; i++){
            args[words][i] = input[last_word_index + i];
        }
        args[words][i] = '\0';

        last_word_index = index + 1;

        // Only increment words if anything has been inputted.
        if(index != 0){
            words++;
        }

        if(words >= MAX_ARGS || chr == '\0'){
            break;
        }
    }

    return words;
}

/* Frees every arg in args. */
static void free_args(char** args){
    int i;
    for(i = 0; i < MAX_ARGS; i++){
        free(args[i]);
        args[i] = NULL;
    }
}

/* Removes all whitespace before and after first and last none
space characters */
static void strip_whitespace(char* input){
    int index, i, length;
    char chr;

    length = strlen(input);

    // Remove trailing whitespace first.
    index = length;
    while(--index > 1 && input[index] == ' ');
    input[++index] = '\0';
    length = index;

    // Remove preceding whitespace.
    index = -1;
    while((chr = input[++index]) == ' ' && chr != '\0');
    for(i = index; i < length; i++){
        input[i - index] = input[i];
    }
    input[length - index] = '\0';
}

static int network_io_loop(){
    while(state.program_running){
        block_until(&state.network_running);
    }
}

/* BLocks until boolean is set to TRUE or program_running is set to FALSE. */
static void block_until(int* boolean){
    while(state.program_running && !(*boolean)){
        do_sleep(SECONDS_TO_SLEEP_NETWORK);
    }
}

/* Sleeps for n seconds, no warning if sleep is cut short. */
static void do_sleep(unsigned seconds){
    #ifdef _WIN32
    Sleep(seconds * 1000);
    #else
    sleep(seconds);
    #endif
}

/* Sets state of the program to not running */
void quit_command(char* args[]){
    state.program_running = FALSE;
    state.network_running = FALSE;
}

void join_command(char* args[]){

}
