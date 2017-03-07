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
    COMMAND_STATE
};

char* INPUT_STATE_NAMES[] = {
    "Command",
    "Message",
    "Settings",
    "Join Network"
    "Input Password"
    "Create Network"
    "Set Password"
};

// --------- Command state commands ------------------
const char* COMMAND_STATE_COMMANDS[NUM_COMMAND_STATE_COMMANDS] = {
    "quit",
    "join",
    "help",
    "h",
    "settings",
    "create",
};

Commandptr_t COMMAND_STATE_FUNCS[NUM_COMMAND_STATE_COMMANDS] = {
    quit_command,
    join_command,
    help_command,
    help_command,
    settings_command,
    create_command
};

// --------- Message state commands ------------------
const char* MESSAGE_STATE_COMMANDS[NUM_MESSAGE_STATE_COMMANDS] = {
    ":help",
    ":return"
};

Commandptr_t MESSAGE_STATE_FUNCS[NUM_MESSAGE_STATE_COMMANDS] = {
    help_command,
    return_command
};

// --------- Settings state commands ------------------
const char* SETTINGS_STATE_COMMANDS[NUM_SETTINGS_STATE_COMMANDS] = {
    "save",
    "reset",
    "discard",
    "help",
    "return"
};

Commandptr_t SETTINGS_STATE_FUNCS[NUM_SETTINGS_STATE_COMMANDS] = {
    save_settings_command,
    reset_settings_command,
    discard_settings_command,
    help_command,
    return_command
};

// --------- Join network state commands ------------------
const char* JOIN_NETWORK_STATE_COMMANDS[NUM_JOIN_NETWORK_STATE_COMMANDS] = {
    "return"
};

Commandptr_t JOIN_NETWORK_STATE_FUNCS[NUM_JOIN_NETWORK_STATE_COMMANDS] = {
    return_command
};

// --------- Input password state commands ------------------
const char* INPUT_PASSWORD_STATE_COMMANDS[NUM_INPUT_PASSWORD_STATE_COMMANDS] = {
    "return"
};

Commandptr_t INPUT_PASSWORD_STATE_FUNCS[NUM_INPUT_PASSWORD_STATE_COMMANDS] = {
    return_command
};

// --------- Create network state commands ------------------
const char* CREATE_NETWORK_STATE_COMMANDS[NUM_CREATE_NETWORK_STATE_COMMANDS] = {
    "return"
};

Commandptr_t CREATE_NETWORK_STATE_FUNCS[NUM_CREATE_NETWORK_STATE_COMMANDS] = {
    return_command
};

// --------- Command state commands ------------------
const char* SET_PASSWORD_STATE_COMMANDS[NUM_SET_PASSWORD_STATE_COMMANDS] = {
    "return"
};

Commandptr_t SET_PASSWORD_STATE_FUNCS[NUM_SET_PASSWORD_STATE_COMMANDS] = {
    return_command
};

// Don't read help and welcome messages from a file in case
// files are not accessible.
//XXX: Keep updating this as more commands are added.
char* HELP_MESSAGE =
    "\n"
    "Current state is given before prompt (e.g. Command->)\n"
    "return: can be used in any state but command to return to "
    "command state\n\n"
    "Command state commands:\n"
    "\tsettings: switches state to settings.\n"
    "\tcreate: switches to create network state allowing creation of networks\n"
    "\tjoin: switches to join network state to allow joining of networks\n"
    "\tquit: quits program when in command state.\n"
    "\n"
    "Settings state commands:\n"
    "\t[setting] = [val]: sets setting setting to val\n"
    "\tsave: saves the current settings\n"
    "\treset: resets settings to default\n"
    "\tdiscard: discards current settings\n"
    "\n"
    "Join network state commands:\n"
    "\t[network name]: attempts to join the specified network\n"
    "\n"
    "Messaging state commands:\n"
    "\t[message]: send message to network\n"
    "\t:help: Displays help while in messaging state\n"
    "\t:return: leaves network\n"
    "\n"
    "Input password state commands:\n"
    "\t[password]: input the password\n"
    "\n"
    "Create network state commands:\n"
    "\t[network name]: Attempts to create the specified network\n"
    "\n"
    "Set password state:\n"
    "\t[password]: Sets the password before creating network.\n"
    "\n";

char* WELCOME_MESSAGE =
    "Welcome to C-Messager.\n"
    "Type help or h to get help.";

/* Starts user input thread and worker threads (if any). */
void start_program(){
    uio_init();
    uio_display(WELCOME_MESSAGE);

    // Start worker threads (if any here).

    start_user_input();
}

void start_user_input(){
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
        uio_display_nn(INPUT_STATE_NAMES[state.input_state]);
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

    char** state_commands;
    Commandptr_t* state_funcs;
    int num_state_commands;
    Commandptr_t default_command = NULL;

    // Work out which state the program is in.
    switch(state.input_state){

        case COMMAND_STATE:
            state_commands = (char**) COMMAND_STATE_COMMANDS;
            state_funcs = COMMAND_STATE_FUNCS;
            num_state_commands = NUM_COMMAND_STATE_COMMANDS;
            break;

        case MESSAGE_STATE:
            state_commands = (char**) MESSAGE_STATE_COMMANDS;
            state_funcs = MESSAGE_STATE_FUNCS;
            num_state_commands = NUM_MESSAGE_STATE_COMMANDS;
            default_command = message_command;
            break;

        case SETTINGS_STATE:
            state_commands = (char**) SETTINGS_STATE_COMMANDS;
            state_funcs = SETTINGS_STATE_FUNCS;
            num_state_commands = NUM_SETTINGS_STATE_COMMANDS;
            default_command = set_setting_command;
            break;

        case JOIN_NETWORK_STATE:
            state_commands = (char**) JOIN_NETWORK_STATE_COMMANDS;
            state_funcs = JOIN_NETWORK_STATE_FUNCS;
            num_state_commands = NUM_JOIN_NETWORK_STATE_COMMANDS;
            default_command = join_network_command;
            break;

        case INPUT_PASSWORD_STATE:
            state_commands = (char**) INPUT_PASSWORD_STATE_COMMANDS;
            state_funcs = INPUT_PASSWORD_STATE_FUNCS;
            num_state_commands = NUM_INPUT_PASSWORD_STATE_COMMANDS;
            default_command = input_password_command;
            break;

        case CREATE_NETWORK_STATE:
            state_commands = (char**) CREATE_NETWORK_STATE_COMMANDS;
            state_funcs = CREATE_NETWORK_STATE_FUNCS;
            num_state_commands = NUM_CREATE_NETWORK_STATE_COMMANDS;
            default_command = create_network_command;
            break;

        case SET_PASSWORD_STATE:
            state_commands = (char**) SET_PASSWORD_STATE_COMMANDS;
            state_funcs = SET_PASSWORD_STATE_FUNCS;
            num_state_commands = NUM_SET_PASSWORD_STATE_COMMANDS;
            default_command = set_password_command;
            break;
    }

    if(num_args == 0){
        // Don't display anyting.
        return;
    }

    command = args[0];

    // Run functions.
    for(i = 0; i < num_state_commands; i++){
        if(strcmp(command, state_commands[i]) == 0){
            state_funcs[i](args);
            return;
        }
    }

    // Run default if there is one.
    if(default_command != NULL){
        default_command(args);
    }

    // If function gets this far then no command has been run.
    uio_display(INVALID_COMMAND_MESSAGE);
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

// -------------- Specific program commands --------------

/* Sets state of the program to not running */
void quit_command(char* args[]){
    state.program_running = FALSE;
    state.network_running = FALSE;
}

/* Joins a messaging network. */
void join_command(char* args[]){
    state.input_state = JOIN_NETWORK_STATE;
}

/* Creates a messaging network. */
void create_command(char* args[]){
    state.input_state = CREATE_NETWORK_STATE;
}

/* Prints the help command */
void help_command(char* args[]){
    uio_display(HELP_MESSAGE);
}

/* Opens settings menu. */
void settings_command(char* argsp[]){
    // XXX: display settings here.
    state.input_state = SETTINGS_STATE;
}

/* Returns to command state. */
void return_command(char* args[]){
    state.input_state = COMMAND_STATE;
}

/* Saves settings. */
void save_settings_command(char* args[]){

}

/* Resets the settings to defaults. */
void reset_settings_command(char* args[]){

}

/* Discards settings set in the since switching to settings state. */
void discard_settings_command(char* args[]){

}

/* Sets the settings given by args. */
void set_setting_command(char* args[]){

}

/* Join a network. */
void join_network_command(char* args[]){

}

/* Sends message to currently joined network. */
void message_command(char* args[]){

}

/* Takes a password in args and tries to log into network. */
void input_password_command(char* args[]){

}

/* Takes name given in args and sets state to set_password_state. */
void create_network_command(char* args[]){

}

/* Sets a password for a network and then creates it. */
void set_password_command(char* args[]){

}
