#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h> // Arduino core library
#include <avr/io.h> // I/O registers
#include <avr/interrupt.h> // Functions and macros related to interrupts
#include <avr/sleep.h> // Microcontroller sleep modes
#include <avr/power.h> // Power management functions

void endGame(); // Ends the game and saves the high score
void initializeGame(); // Initializes game variables
void checkGame(int pressedButton); // Checks the validity of the player's button press
void startTheGame(void); // Starts the game from the beginning
void checkStartCondition(void); // Checks if the conditions to start the game are met
void handleGameLoop(void); // Main loop of the game. Manages game progression
void initializeTimer(void); // Initializes Timer1 and interrupts
void initializeGameComponents(void); // Initializes game components like buttons and LEDs

#endif
