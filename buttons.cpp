#include "buttons.h" // Handling button presses

extern volatile int buttonNumber;  // Used for communicating button number state
extern bool gameStarted;  // References the variable defined in the main program
unsigned long buttonPressStartTime = 0;   // Store the start time of the button press
bool buttonBeingHeld = false;  // Variable to track if the button is being held down

////////// DEBOUNCE //////////
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 300;  // 300 milliseconds debounce delay

////////// BUTTON AND INTERRUPT INITIALIZATION //////////
void initButtonsAndButtonInterrupts(void) {
    // Initialize the game buttons (pins 2-5) as inputs
    for (byte pin = firstPin; pin <= lastPin; pin++) {
        pinMode(pin, INPUT_PULLUP);  // Internal pull-up resistor enabled
    }

    // Enable Pin Change Interrupt for port D (pins 2-5)
    PCICR |= (1 << PCIE2);  // Enable pin change interrupts for port D (pin 16-23)
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21); // Enable interrupts
    // for pins 2, 3, 4, and 5 to detect changes
}

////////// INTERRUPT HANDLING AND DEBOUNCING //////////
ISR(PCINT2_vect) {
    // Check if the debounce time has elapsed
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime) > debounceDelay) {
        // Check which button is pressed and update buttonNumber
        for (byte pin = firstPin; pin <= lastPin; pin++) {
            if (digitalRead(pin) == LOW) {  // If the button is pressed
                buttonNumber = pin;  // Update buttonNumber
                lastDebounceTime = currentTime;  // Update debounce timer
                break;  // Stop checking at the first pressed button
            }
        }
    }
}
