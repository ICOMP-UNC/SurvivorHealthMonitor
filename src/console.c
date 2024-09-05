#pragma once
#include "../include/console.h"
#include <stdlib.h>
int consoleIO(console_t(*callback)()) {
  console_t console;
  console.default_header = "";
  console.default_footer = "";
  console_t new_console = callback();
  console.state = new_console.state;
  console.console_status = new_console.console_status;
  console.console_message = new_console.console_message;
  
  if(console.console_status != _STATUS_OK){
    printf("%s\n", "Error: ");
  }
  print("%s\n", console.default_header);
  printf("%s\n", console.console_message);
  printf("%s\n", console.default_footer);
  consoleStatesHandler(console);
  return 0;
}

void consoleStatesHandler(console_t console) {

  switch(console.state){
    case CONSOLE_INIT:
      delay(2);
      system("clear");
      consoleIO(consoleExit);
      break;
    case CONSOLE_EXIT:
      exit(0);
      break;
    case CONSOLE_ERROR:
      consoleIO(consoleError);
      break;
    case CONSOLE_PRINT_DATA:
      consoleIO(consolePrintData);
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

}

console_t consoleMainMenu() {

}


