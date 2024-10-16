#include "display.h" // Functions related to display control
#include <Arduino.h> // Arduino core library

extern int latchPin; // Latch pin for the shift register
extern int clockPin; // Clock pin for the shift register
extern int dataPin; // Data pin for the shift register
extern byte sevenSegDigits[]; // Array for the 7-segment display numbers

////////// DISPLAY INITIALIZATION //////////
void initializeDisplay(void) {
    pinMode(latchPin, OUTPUT); // Set latch pin to output mode
    pinMode(clockPin, OUTPUT); // Set clock pin to output mode
    pinMode(dataPin, OUTPUT); // Set data pin to output mode
    digitalWrite(latchPin, LOW);  // Ensure that output is LOW at the start
}

////////// DISPLAY UPDATE //////////
void updateShiftRegister(int tensDigit, int onesDigit, bool showDots, int hundreds) {
    digitalWrite(latchPin, LOW); // Prepare to send data to the shift register

    byte onesSegment = sevenSegDigits[onesDigit]; // Get value for the right segment
    byte tensSegment = sevenSegDigits[tensDigit]; // Get value for the left segment

    // If dots should be shown in high score condition
    if (showDots) {
        onesSegment |= B10000000;  // Turn on the dot for the right segment
        tensSegment |= B10000000;  // Turn on the dot for the left segment
    }

    // Add logic for indicating hundreds exceeded
    if (hundreds == 1) {
        onesSegment |= B10000000;  // Turn on the dot for the right segment
    } else if (hundreds >= 2) {
        onesSegment |= B10000000;  // Turn on the dot for the right segment
        tensSegment |= B10000000;  // Turn on the dot for the left segment
    }

    // Shift the segment values into the shift register
    shiftOut(dataPin, clockPin, MSBFIRST, onesSegment);  // Send the right number
    shiftOut(dataPin, clockPin, MSBFIRST, tensSegment);  // Send the left number

    digitalWrite(latchPin, HIGH); // Lock the data into the shift register and update the display
}

////////// CLEAR DISPLAY //////////
void clearDisplay() {
    digitalWrite(latchPin, LOW); // Prepare to send data to the shift register

    // Send zeros to both segments
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);  // Clear the right number
    shiftOut(dataPin, clockPin, MSBFIRST, 0x00);  // Clear the left number

    digitalWrite(latchPin, HIGH); // Lock the data and clear the display
}
