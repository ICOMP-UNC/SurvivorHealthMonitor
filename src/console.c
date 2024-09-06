/**
 * @details This file contains the main console functions.
 * Manual:
 * - consoleIO: Every time is called, does the same process. May be operated recursively.
 * - consoleStatesHandler: Manage next state considering the last state that is passed. Here is also the logic to be implemented if states have input data.
 * - Each console_t struct has various attributes that are used to manage the console. All attributes must be initialized on the console-feature functions.
 * - Console-feature functions are functions that generate an specific console. They must return a console_t struct.
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

static console_t* global_console;

int consoleIO(console_t(*callback)()) {
  console_t* console = getConsole();
  system("clear");
  console->default_header = CONSOLE_HEADER_MESSAGE;
  console->default_footer = CONSOLE_FOOTER_MESSAGE;
  console_t new_console = callback();
  console->input_data_function = new_console.input_data_function;
  console->state_with_input_data = new_console.state_with_input_data;
  console->state = new_console.state;
  console->state_with_PETC = new_console.state_with_PETC;
  console->console_status = new_console.console_status;
  console->console_message = new_console.console_message;
    
    if(console->console_status != _STATUS_OK){            //Error handling. Need more implementation.
    printf("%s\n", "Error: ");
    exit(_STATUS_ERR);
    }
  
  printf("%s\n", console->default_header);
  printf("%s\n", console->console_message);

    if(console->state_with_PETC) {
      printf("%s\n", CONSOLE_PETC);
    }

  printf("%s\n", console->default_footer);

    if(console->state_with_input_data) {
      console->input_data = console->input_data_function();
    }

          if(console->state_with_PETC) {          // Press Enter to Continue input 
            getchar();                            
            getchar();
          }

  consoleStatesHandler(console);
  
  //Bad implementation of recursion. Think about a better way to do this. When exit is called, 
  //the system need to finish all states to end the recursion.
  //---Code goes here when the system has finished and recursion is over---
  return _STATUS_OK;
}

/**
 * @brief Manage where the application should go next
 * Preferably, this function should not have any big logic, and should only call other functions.
 * There are various tools to manage the consoleIO current state to help with that.
 * Should have the input data logic if the state requires it.
 * @param console current console from consoleIO
 */


void consoleStatesHandler(console_t* console) {
  
  switch(console->state){
    case CONSOLE_WELCOME:
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
      consoleIO(consoleMainMenu);
      break;
    case CONSOLE_MAIN_MENU:
    //Ugly implementation. Think about a better way to do this
      
      if(console->input_data == "1") {
        consoleIO(consolePrintData);
      } else if(console->input_data == "2") {
        consoleIO(consoleWelcome);
      } else if(console->input_data == "3") {
        consoleIO(consoleExit);
      } else {
        consoleIO(consoleError);
      }      

      break;
    default:
      break;
  }
}

//-----------------------------Console feature functions-----------------------------------
//All console feature functions must be completed with all the attributes of the console_t struct.

console_t consoleWelcome() {
  console_t console_welcome;
  console_welcome.state_with_input_data = false;
  console_welcome.state_with_PETC = false;
  console_welcome.state = CONSOLE_WELCOME;
  console_welcome.console_status = _STATUS_OK;
  console_welcome.console_message = CONSOLE_WELCOME_MESSAGE; //Giuli you implement this
  console_welcome.state_with_input_data = false;
  return console_welcome;
}

console_t consoleExit() {
  console_t console_exit;
  console_exit.state_with_input_data = false;
  console_exit.state_with_PETC = false;
  console_exit.state = CONSOLE_EXIT;
  console_exit.console_status = _STATUS_OK;
  console_exit.console_message = CONSOLE_EXIT_MESSAGE;      //And this
  return console_exit;
}

console_t consoleError() {
  console_t console_error;
  console_error.state_with_input_data = false;
  console_error.state_with_PETC = false;
  console_error.state = CONSOLE_ERROR;
  console_error.console_status = _STATUS_ERR;
  console_error.console_message = CONSOLE_ERROR_MESSAGE;  //And this   
  return console_error;
}

console_t consolePrintData() {
  updateData();
  console_t console_print_data;
  console_print_data.state = CONSOLE_PRINT_DATA;
  console_print_data.state_with_input_data = false;
  console_print_data.state_with_PETC = true;
  console_print_data.console_status = _STATUS_OK;
  console_print_data.console_message = CONSOLE_PRINT_DATA_MESSAGE; 
  return console_print_data;
}

console_t consoleMainMenu() {
  console_t console_main_menu;
  console_main_menu.state = CONSOLE_MAIN_MENU;
  console_main_menu.state_with_PETC = false;
  console_main_menu.console_status = _STATUS_OK;
  console_main_menu.console_message = CONSOLE_MAIN_MENU_MESSAGE; 
  console_main_menu.state_with_input_data = true;
  console_main_menu.input_data_function = consoleMainMenuInput;
  return console_main_menu;
}

//--------------------------------------------------------------------------------
/**
 * @brief Functions that require input data should be created like this.
 * this is an example. Not real implementation.
 * 
 */

//-----------------------------Input data functions-----------------------------------
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

//--------------------------------------------------------------------------------
/**
 * @brief Get the Console location on memory
 * 
 * @return console_t* The console that has been generated on init
 */
console_t* getConsole() {
  if(global_console == NULL) {
    consoleInit();
  }
  return global_console;
}
/**
 * @brief Initialize console, allocating memory and assigning it to global_console
 * 
 */
void consoleInit() {
  global_console = (console_t*)malloc(sizeof(console_t));  
}

/**
 * @brief Get data from board. Calls getData from main
 * This is called from consolePrintData to show latest data
 * 
 */


void updateData(){
  CONSOLE_PRINT_DATA_MESSAGE = getData();  
}


//Giuli you can make functions following the pattern of the manual above.
//You can also create new states on include/console.h and implement them here.
//If you need (recommended) to create new functions to modularize the code, you can do it on this file or new ones.
//For example, if you want to include ASCII art, maybe you can create 
//a "ASCIIArtGenerator.c", or something like that, and call it from here.
//Even if you want you can include new attributes on the console_t struct, like a "char* ascii_art" attribute.
//Remember to initialize the new attributes on the console-feature functions. Errors will be thrown if you dont do it.
