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

    /* This is user input state. Deciding what the user input should do. */
    int input_state;
};

// Input states.
#define COMMAND_STATE 0
#define MESSAGE_STATE 1
#define SETTINGS_STATE 2
#define JOIN_NETWORK_STATE 3
#define INPUT_PASSWORD_STATE 4
#define CREATE_NETWORK_STATE 5
#define SET_PASSWORD_STATE 6

typedef void (*Commandptr_t)(char* args[]);

#define SECONDS_TO_SLEEP_NETWORK 0.1
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

#define NUM_COMMAND_STATE_COMMANDS 6
#define NUM_MESSAGE_STATE_COMMANDS 2
#define NUM_SETTINGS_STATE_COMMANDS 5
#define NUM_JOIN_NETWORK_STATE_COMMANDS 1
#define NUM_INPUT_PASSWORD_STATE_COMMANDS 1
#define NUM_CREATE_NETWORK_STATE_COMMANDS 1
#define NUM_SET_PASSWORD_STATE_COMMANDS 1

// Command state commands.
void quit_command(char* args[]);
void join_command(char* args[]);
void create_command(char* args[]);
void help_command(char* args[]);
void settings_command(char* argsp[]);

void return_command(char* args[]);

// Settings state commands.
void save_settings_command(char* args[]);
void reset_settings_command(char* args[]);
void discard_settings_command(char* args[]);
void set_setting_command(char* args[]);

// Join network state commands.
void join_network_command(char* args[]);

// Messaging state commands.
void message_command(char* args[]);

// Input password commands.
void input_password_command(char* args[]);

// Create network state commands.
void create_network_command(char* args[]);

// Set password state commands.
void set_password_command(char* args[]);


#endif
