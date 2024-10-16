#include <stdlib.h> // Standard C library
#include <EEPROM.h> // EEPROM memory for storage
#include "display.h" // Functions related to display management
#include "buttons.h" // Handling button presses
#include "leds.h" // LED management
#include "SpedenSpelit.h" // Main program header file
#include "highscore.h" // Highscore handling
#include "sound.h" // Sound effects

////////// POWER SAVING MODE //////////
unsigned long lastActivityTime = 0;  // Time of last activity
const unsigned long inactivityPeriod = 60000;  // wait for 1 minute (60000 ms)
bool deviceSleeping = false;  // Is the device in sleep mode or not

////////// GAME STATE VARIABLES AND INTERRUPTS //////////
// Volatile variables for interrupts and program communication
volatile int buttonNumber = -1;           // Identification of the pressed button
volatile bool newTimerInterrupt = false;  // Timer interrupt

int currentLed = -1;  // Keeps track of which LED is currently lit
int correctPressCount = 0;  // Number of correct presses
int hundredMultiplier = 0;  // Tracks how many times the score has exceeded 99
float timerFrequency = 1.0;  // Timer1's initial frequency is 1 Hz
bool gameStarted = false; // Is the game running
bool gameJustStarted = false;  // The game has just started

Highscore highscore;  // Create a Highscore object

////////// SHIFT REGISTER PINS FOR SEGMENT DISPLAY //////////
int latchPin = 10;  // Connected to ST_CP on 74HC595
int clockPin = 11;  // Connected to SH_CP on 74HC595
int dataPin = 12;   // Connected to DS on 74HC595

////////// ARRAY FOR NUMBERS 0-9 FOR SEGMENT DISPLAY //////////
byte sevenSegDigits[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

////////// POWER SAVING MODE MANAGEMENT //////////
void wakeUp() {
    // Empty function. This wakes the Arduino from sleep mode
}

void sleepModeInterruptsSetup() {
    // Set up the interrupt that wakes the device from button D2
    attachInterrupt(digitalPinToInterrupt(2), wakeUp, LOW);
}

void enterSleepMode() {
    Serial.println("Putting the device to sleep...");

    // Turn off all LEDs and display
    clearAllLeds();
    clearDisplay();

    deviceSleeping = true;  // Set the device to sleep mode

    // Set up sleep mode
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    // Clear interrupt flags
    EIFR = bit (INTF0);

    // Allow interrupts to wake the device
    sleepModeInterruptsSetup();

    // Enter sleep mode. The device will stop here
    endGame(); // End the game
    sleep_mode(); // Go to sleep

    // From this point, the device continues when D2 is pressed and it wakes from sleep

    sleep_disable();  // Disable sleep mode
    detachInterrupt(digitalPinToInterrupt(2));  // Disable interrupt when the device is awake

    deviceSleeping = false; // Device status is out of sleep mode
    Serial.println("The device woke up from sleep.");
    lastActivityTime = millis();  // Update the last activity time so that sleep mode can be recalculated if necessary
}

////////// SETUP //////////
void setup() {
    initializeGameComponents(); // Initialize all components
    initializeSpeaker(); // Initialize speaker
    lastActivityTime = millis();  // Initialize last activity time
    detachInterrupt(digitalPinToInterrupt(2)); // Ensure there are no overlapping interrupts
    ///resetHighscore();  // Reset highscore (this is used only during testing)
}

////////// LOOP //////////
void loop() {
    unsigned long currentTime = millis(); // Store current time in milliseconds
    // Check if any button is pressed
    if (digitalRead(2) == LOW || digitalRead(3) == LOW || digitalRead(4) == LOW || digitalRead(5) == LOW) {
        lastActivityTime = currentTime;  // Update last activity time when a button is pressed
    }
    
    // Check if the device is in sleep mode
    if (!deviceSleeping) {
        // If the game hasn't started yet, check the start conditions
        if (!gameStarted) {
            checkStartCondition();
        }
        // If the game is running, execute the main game loop
        if (gameStarted) {
            handleGameLoop();
        }
        // Check if enough time has passed since the last button press
        if (currentTime - lastActivityTime >= inactivityPeriod) {
            enterSleepMode();  // Put the device to sleep
        }
    }
}

////////// THIS IS FOR DEBUGGING //////////
void resetHighscore() {
  // Reset the high score by storing the value 0 in EEPROM memory
  EEPROM.update(0, 0);             // Lower byte
  EEPROM.update(1, 0);             // Upper byte
}
