#pragma once
#include "../include/console.h"
#include <stdlib.h>

/**
 * @brief Main console function
 * 
 * Prints header and footer on default, and calls the callback function to 
 * update the console system.
 * Checks for errors and prints them.
 * Checks if the console state requires input data and call the input_data function.
 * Finally, calls consoleStatesHandler to manage the next state.
 * @param callback 
 * @return int 
 */
int consoleIO(console_t(*callback)()) {
  console_t console;
  console.default_header = "";
  console.default_footer = "";
  console_t new_console = callback();
  console.input_data_function = new_console.input_data_function;
  console.state_with_input_data = new_console.state_with_input_data;
  console.state = new_console.state;
  console.console_status = new_console.console_status;
  console.console_message = new_console.console_message;
  
  if(console.console_status != _STATUS_OK){
    printf("%s\n", "Error: ");
  }

  
  printf("%s\n", console.default_header);
  printf("%s\n", console.console_message);
  printf("%s\n", console.default_footer);
  if(console.state_with_input_data) {
    console.input_data = console.input_data_function();
    printf("%s\n", console.input_data);
  }
  consoleStatesHandler(console);
  return 0;
}

/**
 * @brief Manage where the application should go next
 * Preferably, this function should not have any big logic, and should only call other functions.
 * There are various tools to manage the consoleIO current state to help with that.
 * 
 * @param console current console from consoleIO
 */
void consoleStatesHandler(console_t console) {

  switch(console.state){
    case CONSOLE_INIT:
      delay(2);
      system("clear");
      consoleIO(consolePrintData);
      break;
    case CONSOLE_EXIT:
    system("clear");
      exit(0);
      break;
    case CONSOLE_ERROR:
      consoleIO(consoleError);
      break;
    case CONSOLE_PRINT_DATA:
      delay(2);
      consoleIO(consoleExit);
      break;
    case CONSOLE_MAIN_MENU:
      consoleIO(consoleMainMenu);
      break;
    default:
      break;
  }
}
console_t consoleInit() {

  console_t console_init;
  console_init.state = CONSOLE_INIT;
  console_init.console_status = _STATUS_OK;
  console_init.console_message = "Bienvenidos";
  console_init.state_with_input_data = false;
  return console_init;
}

console_t consoleExit() {
  console_t console_exit;
  console_exit.state = CONSOLE_EXIT;
  console_exit.console_status = _STATUS_OK;
  console_exit.console_message = "Chau";
  return console_exit;
}

console_t consoleError() {

}

console_t consolePrintData() {
  console_t console_print_data;
  console_print_data.state = CONSOLE_PRINT_DATA;
  console_print_data.console_status = _STATUS_OK;
  console_print_data.console_message = "Elige un valor para imprimir: 1, 2 o 3";  //example here
  console_print_data.state_with_input_data = true;
  console_print_data.input_data_function = consolePrintDataInput;
  return console_print_data;
}

console_t consoleMainMenu() {

}

/**
 * @brief Functions that require input data should be created like this.
 * this is an example. Not real implementation.
 * 
 */
char* consolePrintDataInput() {
  int input;
  scanf("%d", &input);
  if(input == 1) {
    printf("%s\n", "Imprimiendo 1");
    return "1";
  } else if(input == 2) {
   
    printf("%s\n", "Imprimiendo 2");
     return "2";
  } else if(input == 3) {
    printf("%s\n", "Imprimiendo 3");
    return "3";
  } else {
    consoleIO(consoleError);
  }
}

