/**
 * @brief All console functions. 
 * @author 
 * @date 
 */

#pragma once
#include <stdbool.h>
#define _STATUS_OK 0
#define _STATUS_ERR 1
/**
 * @brief possible console states
 /**
 * @brief 
 * 
 */
typedef enum {
    CONSOLE_INIT,
    CONSOLE_EXIT,
    CONSOLE_ERROR,
    CONSOLE_PRINT_DATA,
    CONSOLE_MAIN_MENU
} console_state_t;


/**
 * @brief console struct
 * Has all the necessary information to represent the console.
 * 
 * 
 */

typedef struct {
    bool state_with_input_data;       // If the state requires input data
    bool state_with_PETC;             // If the state requires to press enter to continue
    char* input_data;                 // Input data
    console_state_t state;            // Current state
    char *default_header;             // Default header
    char *default_footer;             // Default footer
    int (*callback_function)();       // Callback function
    char* (*input_data_function)();             // Input data function: Needs to be created for each state that requires input data. If state_with_input_data is true, this functions will be called on consoleIO.               
    int console_status;               // Status of the console
    char *console_message;            // Message to be printed on the console: If screen needs options to be selected on input_data, this message should include the options.
} console_t;
/**
 * @brief Main function for the console 
 * 
 * @return int 
 */
 
int consoleIO(console_t(*)());

/**
 * @brief Handle states
 * 
 */
void consoleStatesHandler(console_t);


/**
 * @brief For each console state that needs input data, a function like this should be created.
 * 
 */
char* consoleMainMenuInput();
/**
 * @brief All console callbacks functions. 
 * 
 * @return console_t 
 */
console_t consoleInit();
console_t consoleExit();
console_t consoleError();
console_t consolePrintData();
console_t consoleMainMenu();

