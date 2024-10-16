#ifndef LEDS_H
#define LEDS_H

#include <arduino.h> // Arduino core library

void initializeLeds();           // Initializes the LEDs
void setLed(byte ledNumber);     // Turns on the specified LED
void clearAllLeds(void);         // Turns off all LEDs
void setAllLeds(void);           // Turns on all LEDs
void show1(void);                // Displays binary representation of numbers 0-15 with LEDs
void show2(int rounds);          // Turns on LEDs in an accelerating sequence

#endif
