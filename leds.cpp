#include "leds.h" // LED control

////////// LED PIN ASSIGNMENTS //////////
const byte ledPins[] = {A1, A2, A3, A4};  // LEDs are connected to pins A1-A4
byte lastLed = 255;  // Initialize with a value that is not a valid LED number

////////// LED INITIALIZATION //////////
void initializeLeds() {
    // Initialize all LEDs used in the game (4 total)
    for (byte i = 0; i < 4; i++) {
        pinMode(ledPins[i], OUTPUT);  // Set each LED pin to output mode
        digitalWrite(ledPins[i], LOW);  // Turn off all LEDs initially
    }
}

////////// TURN ON/OFF LEDS //////////
void setLed(byte ledNumber) {
    // If a LED is already on and it's not the same as the new LED, turn it off
    if (lastLed != 255 && lastLed != ledNumber) {
        digitalWrite(ledPins[lastLed], LOW);  // Turn off the previous LED
    }
    // Turn on the new LED
    digitalWrite(ledPins[ledNumber], HIGH);
    lastLed = ledNumber;  // Update the last turned-on LED
}

////////// TURN OFF ALL LEDS //////////
void clearAllLeds() {
    for (byte i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], LOW);  // Turn off all LEDs
    }
    lastLed = 255;  // Reset the last turned-on LED
}

////////// TURN ON ALL LEDS //////////
void setAllLeds() {
    for (byte i = 0; i < 4; i++) {
        digitalWrite(ledPins[i], HIGH);  // Turn on all LEDs
    }
}

////////// BINARY REPRESENTATION OF NUMBERS 0-15 WITH LEDS //////////
void show1() {
    // Show numbers 0-15 as binary representations with the LEDs
    for (int i = 0; i < 16; i++) {
        for (byte j = 0; j < 4; j++) {
            if (i & (1 << j)) {
                digitalWrite(ledPins[j], HIGH);  // Turn on LED if the bit is 1
            } else {
                digitalWrite(ledPins[j], LOW);   // Turn off LED if the bit is 0
            }
        }
        delay(500);  // Small delay so the binary display is visible
    }
}

////////// TURN ON LEDS IN ACCELERATING SEQUENCE //////////
void show2(int rounds) {
    // Turn on LEDs 0-3 in an increasingly faster sequence
    int delayTime = 500;  // Initial delay is 500 ms
    for (int r = 0; r < rounds; r++) {
        for (byte i = 0; i < 4; i++) {
            clearAllLeds();  // Turn off all LEDs before lighting a new one
            digitalWrite(ledPins[i], HIGH);  // Turn on LED 0-3
            delay(delayTime); // Wait for the current delay duration
        }
        // Reduce the delay each round, making the sequence faster
        if (delayTime > 100) {
            delayTime -= 50;  // Decrease the delay to speed up the pattern
        }
    }
}
