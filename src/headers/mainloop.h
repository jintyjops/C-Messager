#ifndef MAINLOOP_SRC
#define MAINLOOP_SRC

#include "definitions.h"

struct program_state {
    /* This is set to TRUE when the program is running and FALSE when not running,
    indicating that threads should break out of loops and return. */
    int program_running;
    /* This is TRUE when network io should be on. Should be FALSE
    by default for security reasons. */
    int network_running;
};

typedef void (*Commandptr_t)(char* args[]);

#define SECONDS_TO_SLEEP_NETWORK 0.1
#define NUM_USER_COMMANDS 4
#define MAX_USER_INPUT -1
#define MAX_ARGS 32
#define COMMAND_INPUT_PROMPT "->"

// User messages.
#define INVALID_COMMAND_MESSAGE "That is not a valid command!"

void start_program();
void start_user_input();
void start_network();
static int user_io_loop();
static void parse_user_input(char** args, int num_args);
static int separate_args(char** args, char* input);
static void free_args(char** args);
static void strip_whitespace(char* input);
static int network_io_loop();
static void block_until(int* boolean);
static void do_sleep(unsigned seconds);

// Commands.
void quit_command(char* args[]);
void join_command(char* args[]);
void help_command(char* args[]);

#endif
