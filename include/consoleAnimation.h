/**
 * @brief Animations for Welcome and Exit states of the console. 
 * @author Giuliano Romanello
 * @date 
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/console.h"

#define FRAME_DELAY 200000 
#define MAX_LINE_LENGTH 256 //Up to change, maybe not necessary


/**
 * @brief Reads .txt file
 * Reads welcome.txt or exit.txt depending on the state of the console.
 * 
 * 
 */
char* readFile(console_state_t);

/**
 * @brief Prints the .txt file
 * Prints one frame of the ASCII animation at a time.
 * Each frame is separated by the "START" and "END" strings.
 * 
 */
void printFile(FILE*);