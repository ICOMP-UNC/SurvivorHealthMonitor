/*
 * @file main.c
 * @brief Main file for the project.
 * Copyright (C) 2024
 * August 30, 2024.
 *
 * MIT License
 */

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  system();
  printf("Hello World!\n");
  
  // console(update()); Cada vez que pase por aca, la consola se actualizara con los
  // datos del sistema.
  __clock_t start = clock();
  __clock_t dt = clock() - start;
  while(clock() - start  < CLOCKS_PER_SEC * 0.1 ){
    printf("Welcome.\n");
    
  }
  return 0;
}
