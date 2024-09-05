/*
 * @file main.c
 * @brief Main file for the project.
 * Copyright (C) 2024
 * August 30, 2024.
 *
 * MIT License
 */

#include <stdio.h>
#include "../include/timeController.h"
#include <time.h>
#include "console.c"
int main(int argc, char *argv[]) {
  consoleIO(consoleInit);
  
  
  
  
  return 0;
}

void delay(double seconds) {
  __clock_t initial_timestamp = clock();
  __clock_t delta_time = clock() - initial_timestamp;
  while(clock() - initial_timestamp  < CLOCKS_PER_SEC * seconds ){
    //do nothing
  }
}

