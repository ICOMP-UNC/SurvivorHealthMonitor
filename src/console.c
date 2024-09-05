/**
 * @details This file contains the main console functions.
 * Manual:
 * - consoleIO: Every time is called, does the same process. May be operated recursively.
 * - consoleStatesHandler: Manage next state considering the last state that is passed.
 * - Each console_t struct has various attributes that are used to manage the console.
 * Most important attributes are explained on include/console.h
 * - To manage input data screens, console_t has three attributes:
 *  1.- state_with_input_data: If the state requires input data. ConsoleIO will know how to handle it if this attribute is correctly set.
 *  2.- input_data_function: This has to be declared on this file. Contains the logic to get the input data, and returns char*.
 *  3.- input_data: This is the input data that the user has entered. It is assigned on consoleIO after calling input_data_function.
 * - If the screen not requires input data, the attribute state_with_input_data MUST be set to false.
 * IMPORTANT: All console states must be declared on include/console.h and structs must be initialized on this file, on each console-feature function.
 * 
 * @author Emiliano Castro.
 */

#pragma once
#include "../include/console.h"
#include "../include/consoleScreen.h"
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
  system("clear");
  console_t console;
  console.default_header = CONSOLE_HEADER_MESSAGE;
  console.default_footer = CONSOLE_FOOTER_MESSAGE;
  console_t new_console = callback();
  console.input_data_function = new_console.input_data_function;
  console.state_with_input_data = new_console.state_with_input_data;
  console.state = new_console.state;
  console.console_status = new_console.console_status;
  console.console_message = new_console.console_message;
  
  if(console.console_status != _STATUS_OK){
    printf("%s\n", "Error: ");
    exit(1);
  }

  
  printf("%s\n", console.default_header);
  printf("%s\n", console.console_message);
  printf("%s\n", console.default_footer);
  if(console.state_with_input_data) {
    console.input_data = console.input_data_function();
    //printf("%s\n", console.input_data);
   
  }
  consoleStatesHandler(console);


  //---Code goes here when the system has finished and recursion is over---
  delay(1);
  return 0;
}

/**
 * @brief Manage where the application should go next
 * Preferably, this function should not have any big logic, and should only call other functions.
 * There are various tools to manage the consoleIO current state to help with that.
 * Should have the input data logic if the state requires it.
 * @param console current console from consoleIO
 */
void consoleStatesHandler(console_t console) {

  switch(console.state){
    case CONSOLE_INIT:
      delay(2);
      system("clear");
      consoleIO(consoleMainMenu);
      break;
    case CONSOLE_EXIT:
      system("clear");
      break;
    case CONSOLE_ERROR:
      consoleIO(consoleError);
      break;
    case CONSOLE_PRINT_DATA:
      //delay(2);
      consoleIO(consoleMainMenu);
      break;
    case CONSOLE_MAIN_MENU:
    //Ugly implementation. Think about a better way to do this
      
      if(console.input_data == "1") {
        consoleIO(consolePrintData);
      } else if(console.input_data == "2") {
        consoleIO(consoleInit);
      } else if(console.input_data == "3") {
        consoleIO(consoleExit);
      } else {
        consoleIO(consoleError);
      }      

      break;
    default:
      break;
  }
}

console_t consoleInit() {

  console_t console_init;
  console_init.state = CONSOLE_INIT;
  console_init.console_status = _STATUS_OK;
  console_init.console_message = CONSOLE_INIT_MESSAGE; //Giuli you implement this
  console_init.state_with_input_data = false;
  return console_init;
}

console_t consoleExit() {
  console_t console_exit;
  console_exit.state_with_input_data = false;
  console_exit.state = CONSOLE_EXIT;
  console_exit.console_status = _STATUS_OK;
  console_exit.console_message = CONSOLE_EXIT_MESSAGE;      //And this
  return console_exit;
}

console_t consoleError() {
  console_t console_error;
  console_error.state = CONSOLE_ERROR;
  console_error.console_status = _STATUS_ERR;
  console_error.console_message = CONSOLE_ERROR_MESSAGE;  //And this   
  return console_error;
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
  console_t console_main_menu;
  console_main_menu.state = CONSOLE_MAIN_MENU;
  console_main_menu.console_status = _STATUS_OK;
  console_main_menu.console_message = CONSOLE_MAIN_MENU_MESSAGE; 
  console_main_menu.state_with_input_data = true;
  console_main_menu.input_data_function = consoleMainMenuInput;
  return console_main_menu;
}

/**
 * @brief Functions that require input data should be created like this.
 * this is an example. Not real implementation.
 * 
 */

char* consoleMainMenuInput() {

  int input;
  scanf("%d", &input);
  if(input == 1) {
    return "1";
  } else if(input == 2) {
   
     return "2";
  } else if(input == 3) {
    return "3";
  } else {
    consoleIO(consoleError);
  }
}
char* consolePrintDataInput() {
  getchar();
  printf("%s\n", "DATA TO SHOW");
  printf("%s\n", "Press enter to continue..");
  getchar();
    return " ";
}


//Giuli you can make functions following the pattern of the manual above.
//You can also create new states on include/console.h and implement them here.
//If you need (recommended) to create new functions to modularize the code, you can do it on this file or new ones.
//For example, if you want to include ASCII art, maybe you can create 
//a "ASCIIArtGenerator.c", or something like that, and call it from here.
//Even if you want you can include new attributes on the console_t struct, like a "char* ascii_art" attribute.
//Remember to initialize the new attributes on the console-feature functions. Errors will be thrown if you dont do it.
