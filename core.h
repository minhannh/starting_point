#ifndef CORE_H
#define CORE_H

#include <stdio.h>
// typedef enum { false, true } bool;

/*TODO: If you are using some global variables and you intent to let other
 * users access it, you better declare it here.
 * Hint: use extern as shown in the below
 */
extern bool __coreInitialized;
extern int  __userChoice;
extern bool __isExiting;

/**
 * Function: Initialization
 * Purpose:  Initialize anything necessary in your program before starting
 * Input:    None
 * Output:   None
 */
void Initialization();

/**
 * Function: Finalization
 * Purpose:  Clean up everything before the program exits
 * Input:    None
 * Output:   None
 */
void Finalization();

void LoadConfiguration();

void LoadMenu();

void DisplayMenu();

void ProcessUserChoice();

#endif