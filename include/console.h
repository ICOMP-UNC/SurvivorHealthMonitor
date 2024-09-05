/**
 * @brief All console functions. 
 * @author 
 * @date 
 */

#define _STATUS_OK 0
/**
 * @brief possible console states
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
 * @brief consoleIO
 * 
 * @param callback 
 * @return int 
 */

typedef struct {
    console_state_t state;
    char *default_header;
    char *default_footer;              
    int (*callback_function)();
    int console_status;
    char *console_message;
} console_t;

int consoleIO(console_t(*)());
void consoleStatesHandler(console_t);

console_t consoleInit();
console_t consoleExit();
console_t consoleError();
console_t consolePrintData();
console_t consoleMainMenu();

