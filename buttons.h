#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h> // Arduino core library
#include <avr/io.h> // I/O registers
#include <avr/interrupt.h> // Functions and macros related to interrupts

// Define the pins used for button press interrupts
const byte firstPin = 2; // First Pin Change Interrupt on port D
const byte lastPin =  5; // Last Pin Change Interrupt on port D

void initButtonsAndButtonInterrupts(void); // Initializes buttons and their interrupts
void checkStartButton(void);  // New function to check the game start condition
extern bool gameStarted; // This variable indicates whether the game has started (true = started, false = not started)

// Define the ISR for the PCINT2_vect Pin Change Interrupt
ISR(PCINT2_vect); 

#endif
