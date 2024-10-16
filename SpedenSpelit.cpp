#include "SpedenSpelit.h"  // Main program header file
#include "display.h"       // Functions for managing the display
#include "buttons.h"       // Handling button presses
#include "leds.h"          // LED control
#include "highscore.h"     // Highscore management
#include "sound.h"         // Sound effects
#include <EEPROM.h>        // For EEPROM memory storage
#include <Arduino.h>       // Basic Arduino library

extern int latchPin;       // Shift register latch pin
extern int clockPin;       // Shift register clock pin
extern int dataPin;        // Shift register data pin
extern byte sevenSegDigits[];  // Array for 7-segment display digits
extern int correctPressCount;  // Number of correct button presses
extern bool gameJustStarted;   // Flag indicating the game has just started
extern bool gameStarted;       // Flag indicating the game is active
extern Highscore highscore;    // Highscore object
extern float timerFrequency;   // Timer frequency
extern int currentLed;         // The currently active LED
extern int buttonNumber;       // The number of the button pressed
extern int hundredMultiplier;  // Hundreds points multiplier
extern volatile bool newTimerInterrupt;  // Interrupt event flag
extern unsigned long buttonPressStartTime;  // Timestamp for when button was pressed
extern bool buttonBeingHeld;   // Flag to check if button is being held down
bool buttonPressedForCurrentLed = false;  // Track if the button for the current LED was pressed in time

////////// 2-SECOND PRESS TO START GAME //////////
const unsigned long startPressDuration = 2000;  // 2 seconds

////////// GAME INITIALIZATION //////////
void initializeGame() {
  correctPressCount = 0;   // Reset correct press count
  timerFrequency = 1.0;    // Initialize timer frequency
  gameJustStarted = true;  // Set flag indicating game has just started
  currentLed = -1;         // No LED is lit at the start
  buttonNumber = -1;       // Reset button press
  buttonPressedForCurrentLed = true;  // No LED lit initially
}

////////// INITIALIZE GAME COMPONENTS //////////
void initializeGameComponents(void) {
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    Serial.begin(9600);  // Initialize serial communication
    initButtonsAndButtonInterrupts();  // Initialize buttons and interrupts
    initializeLeds();  // Initialize LEDs

    randomSeed(analogRead(A0));  // Seed random number generator
    timerFrequency = 1.0;  // Set starting frequency
    initializeTimer();  // Initialize Timer1 with 1 Hz frequency
}

////////// CHECK GAME START CONDITIONS //////////
void checkStartCondition(void) {
    const unsigned long blinkInterval = 800;  // LEDs and Highscore blink every 800ms
    const unsigned long onDuration = 250;     // Duration LEDs and highscore stay on
    static unsigned long lastBlinkTime = 0;   // Track last blink time
    unsigned long currentTime = millis();     // Current time in milliseconds
    unsigned long elapsedTime = currentTime - lastBlinkTime;  // Time since the last blink

    // A1 LED blinks before game starts
    if (elapsedTime < onDuration) {
        setLed(0);  // Turn on LED A1

        // Display highscore. Divide hundreds and units
        int score = highscore.getHighscore();
        int highscoreHundreds = score / 100;
        int displayScore = score % 100;
        updateShiftRegister(displayScore / 10, displayScore % 10, false, highscoreHundreds);  // Update display
  
    } else if (elapsedTime < blinkInterval) {
        // Turn off LEDs and display
        clearAllLeds();  // Turn off all LEDs
        clearDisplay();  // Clear the display
    } else {
        lastBlinkTime = currentTime;  // Reset the blink cycle
    }

    // Check if button D2 is held for more than 2 seconds to start the game
    if (digitalRead(2) == LOW) {
        if (!buttonBeingHeld) {
            buttonPressStartTime = currentTime; // Button press started
            buttonBeingHeld = true;  // Mark button as held
            Serial.println("Button D2 pressed");
        }

        // If the button is held for more than 2 seconds, the game starts
        if (currentTime - buttonPressStartTime >= startPressDuration) {
            Serial.println("Starting the game");
            clearAllLeds();  // Turn off all LEDs before game start
            clearDisplay();  // Clear the display
            sound(4);        // Play start sound
            delay(700);      // Wait 700ms before starting the game
            startTheGame();  // Call the function to start the game
            buttonBeingHeld = false;  // Reset button hold
        }
    } else {
        // If the button is released before 2 seconds, reset the state
        if (buttonBeingHeld) {
            Serial.println("Button D2 released before 2 seconds");
        }
        buttonBeingHeld = false;  // Reset button hold
        buttonPressStartTime = 0; // Reset time
    }
}

////////// START THE GAME //////////
void startTheGame(void) {
    initializeGame();       // Initialize game variables
    initializeTimer();      // Start Timer1 interrupts
    gameStarted = true;     // Mark the game as started
}

////////// GAME CHECK AND SCORE MANAGEMENT //////////
void checkGame(int pressedButton) {
  // Check if the correct button was pressed
  if (pressedButton == currentLed) {
    Serial.println("Correct button pressed!");
    correctPressCount++;  // Increment correct press count
    sound(6);  // Play victory sound

    buttonPressedForCurrentLed = true;  // The button was pressed in time

    // Check if the score exceeds 99
    if (correctPressCount > 99) {
      correctPressCount = 0;  // Reset score after exceeding 99
      hundredMultiplier++;    // Increase hundred-point multiplier
    }

    // Update the display with the current score, using a decimal point
    updateShiftRegister(correctPressCount / 10, correctPressCount % 10, false, hundredMultiplier);

    // Speed up the game by 10% after every 10 correct presses
    if (correctPressCount % 10 == 0 && correctPressCount != 0) {
      timerFrequency *= 1.1;   // Increase frequency by 10%
      initializeTimer();       // Set new frequency
      Serial.print("Timer frequency increased to: ");
      Serial.print(timerFrequency, 2); // Print new frequency with 2 decimal places
      Serial.println(" Hz");
    }

    buttonNumber = -1;  // Reset button press
  } else {
    // If the wrong button is pressed, the game ends
    Serial.println("Wrong button pressed! Game over.");
    sound(0);  // Play loser sound
    endGame();  // End the game
  }
}

////////// MAIN GAME LOOP & LED SELECTION //////////
void handleGameLoop(void) {
    // When the game starts for the first time, wait 1 second
    if (gameJustStarted) {
        delay(1000);  // 1 second delay at game start
        gameJustStarted = false;  // Only do this once at the start
    }

    // While the game is running, Timer1 picks new LEDs
    if (newTimerInterrupt) {
        newTimerInterrupt = false;  // Reset interrupt flag

        // Ensure the new LED is different from the current LED
        int newLed;
        do {
            newLed = random(0, 4);  // Pick a new LED (0-3)
        } while (newLed == currentLed);  // Repeat if the new LED is the same as the current one

        currentLed = newLed;  // Set the current LED to the newly selected LED
        clearAllLeds();  // Turn off all LEDs before lighting a new one
        setLed(currentLed);  // Light the new LED

        // Check if the current LED's button was pressed in time
        if (!gameJustStarted && !buttonPressedForCurrentLed) {
            Serial.println("Time exceeded, game over.");
            sound(0);  // Play loser sound
            endGame();  // End the game
            return;  // Exit function
        }

        buttonPressedForCurrentLed = false;  // Reset the press status for the current LED

        // Display the game score on the 7-segment display
        updateShiftRegister(correctPressCount / 10, correctPressCount % 10, false, hundredMultiplier);  // Update the score on the display
    }

    // Check if a button is pressed and if it's the correct one
    if (buttonNumber >= 2 && buttonNumber <= 5) {
        int pressedButton = buttonNumber - 2;  // Convert button number to match LED (0-3)
        checkGame(pressedButton);              // Check if the press was correct
        buttonNumber = -1;  // Reset button number for the next press
    }
}

////////// THE END & HIGHSCORE //////////
void endGame() {
    // Calculate the total score
    int totalScore = (hundredMultiplier * 100) + correctPressCount;

    // Save the highscore only if the new score is better
    if (totalScore > highscore.getHighscore()) {
        highscore.setHighscore(totalScore);  // Update Highscore
    }

    // Reset game variables for the next round
    correctPressCount = 0;  // Reset correct press counter
    hundredMultiplier = 0;  // Reset hundred multiplier
    gameJustStarted = false; // Reset the game start state
    gameStarted = false; // Mark the game as ended

    // Turn off LEDs and display
    clearAllLeds(); // Turn off all LEDs
    clearDisplay(); // Clear the 7-segment display
}

////////// TIMER1 INITIALIZATION AND INTERRUPT CONFIGURATION //////////
void initializeTimer(void) {
    float frequency = timerFrequency;  // Use the timer frequency defined globally

    cli();  // Disable interrupts during configuration
    TCCR1A = 0;  // Set Timer1 to normal mode
    TCCR1B = 0;  // Reset Timer1
    TCNT1 = 0;   // Reset Timer1 counter

    // Calculate the interrupt interval
    int compareMatch = (int)(16000000 / (1024 * frequency)) - 1;

    OCR1A = compareMatch;  // Set the timer interrupt value
    TCCR1B |= (1 << WGM12);  // CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10);  // Set prescaler to 1024

    TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 Compare Match A interrupt
    sei();  // Enable interrupts after configuration
}

////////// TIMER1 COMPARE MATCH A INTERRUPT HANDLER //////////
ISR(TIMER1_COMPA_vect) {
    newTimerInterrupt = true;  // Set the interrupt flag - a new timer interrupt has occurred
}
