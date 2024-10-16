#ifndef DISPLAY_H
#define DISPLAY_H

void initializeDisplay(void); // Initializes the 7-segment display
void clearDisplay(); // Clears the display and turns off all segments
// Updates the 7-segment display with tens, ones, an optional decimal point, and hundreds.
void updateShiftRegister(int tensDigit, int onesDigit, bool showDots = false, int hundreds = 0);

#endif
