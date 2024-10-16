# Speden Spelit Reaction Game – Arduino Edition


**Speden Spelit** is an Arduino-based reaction and speed game, inspired by the Finnish TV show of the same name from the 1990s. The player’s goal is to collect points by pressing the button corresponding to the lit LED as quickly as possible.

The device is assembled using Arduino and several components, such as shift registers, 7-segment displays, a speaker, LEDs, and resistors, following a circuit diagram. All components are carefully soldered, installed in a case, and tested for functionality. The code is modularly programmed, making it easy to extend the game’s features as needed.

The game starts by holding the start button for 2 seconds. After that, a start sound plays, and the first LED lights up. The player’s objective is to press the correct button as soon as the corresponding light turns on. After every 10 successful presses, the LED blink speed increases by 10%. The game ends if the player presses the wrong button or fails to press the correct button in time.

During gameplay, the 7-segment displays indicate the game’s progress with the help of sound cues. When the player reaches 100 points, the first decimal point on the display lights up, showing that the score exceeds 99. This repeats at 200 points when the second decimal point turns on. At the end of the game, the score is saved to the device’s memory, where the player’s high score is displayed. If the device is inactive for 60 seconds, it automatically switches to power-saving mode. The device can be reactivated by pressing the start button once.

This introduction presents the **Speden Spelit** device, which combines the excitement of a traditional game with modern electronics. The project was carried out as part of the *Tietotekniikan sovellusprojekti* (Application Project in Information Technology) course at Oulu University of Applied Sciences.

![1](https://github.com/user-attachments/assets/972f775d-fa83-44dd-84c2-7fb483852759)

# Contents

- [Introduction](#speden-spelit-reaction-game--arduino-edition)
- [Directory Structure](#directory-structure)
- [Technical Specifications](#technical-specifications)
- [Assembly](#assembly)
- [Serial Monitor Event Tracking](#serial-monitor-event-tracking)
- [MIT License](#mit-license)
  
# Directory Structure

``` SpedenSpelit/
├── LICENSE.md                # The license file specifying terms for using this project.
├── README.md                 # The main README file explaining the project.
├── SpedenSpelit.cpp          # Core logic of the SpedenSpelit game.
├── SpedenSpelit.h            # Header file for the SpedenSpelit game logic.
├── SpedenSpelit.ino          # Arduino script, the main entry point for the game.
├── buttons/
│   ├── buttons.cpp           # Handles the logic for button presses and interactions.
│   └── buttons.h             # Header file for button functionality.
├── display/
│   ├── display.cpp           # Controls the 7-segment display outputs.
│   └── display.h             # Header file for the display functionality.
├── highscore/
│   ├── highscore.cpp         # Manages the high score logic and data storage.
│   └── highscore.h           # Header file for the high score functionality.
├── leds/
│   ├── leds.cpp              # Controls the LED lighting sequences in the game.
│   └── leds.h                # Header file for LED functionality.
├── sound/
│   ├── sound.cpp             # Manages sound effects and sound output.
│   └── sound.h               # Header file for sound functionality.
```
# Technical Specifications

•	**Circuit Diagram:** The project includes a circuit diagram that shows how the game’s electronic components, such as buttons, LEDs, buzzers, 7-segment displays, and shift registers, are connected to the Arduino.

<img width="1124" alt="2" src="https://github.com/user-attachments/assets/fdcec1b4-6a93-47dd-b74c-f7c8c90cf9d2">

•	**Flowchart:** Explains the game’s logic and the interaction between different functions, helping to visualize the game’s flow.

<img width="787" alt="3" src="https://github.com/user-attachments/assets/786354c4-ffe6-432b-a14f-b9b293479e85">

•	**Code Files:** The program code is divided into modular sections, such as handling buttons, displays, score calculation, and sound effects.

<img width="211" alt="4" src="https://github.com/user-attachments/assets/a2333cb6-ac4f-4f7d-af6a-d5d04d475aa9">

•	**Video Presentation:** A practical demonstration showing the completed device in action. *Click the video below to watch:*

[![Speden Spelit](https://github.com/user-attachments/assets/4d97ec0c-ffa7-4fa9-9d67-6a3f4bffa6d1)](https://youtu.be/qdzAhDunAkY)

# Assembly
**Required Components:**

• Arduino Uno (or equivalent)

• Arduino IDE

• 4x BROADCOM HLMP-4740 LEDs (or equivalent)

• 4x PANASONIC ESE20C321 Buttons

• 2x KINGBRIGHT SC52-11EWA 7-segment displays

• 2x TEXAS INSTRUMENTS SN74HC595N Shift Registers

• Crowtail Speaker

• A sufficient amount of jumper wires and resistors

• A breadboard large enough to accommodate the components

• If preferred, you can also solder the components to a printed circuit board (PCB) and enclose the device in a case.

![5](https://github.com/user-attachments/assets/3250fbfd-de2d-4554-a712-91ae9ffd2afe)

# Serial Monitor Event Tracking:

<img width="268" alt="6" src="https://github.com/user-attachments/assets/bb9debc5-5b6b-4e53-9b15-17d240e1b2f7">

•	**Connections:** The wiring must be done according to the circuit diagram to ensure the game works as intended by the software code. Special attention is needed with the buttons and LEDs to ensure they are connected to the correct ports on the Arduino.

•	**Software Requirements:** You will need the Arduino IDE installed on your computer. Through the IDE, you can upload all files directly to the Arduino.

•	**Uploading Code:** Upload the program code from the SpedenSpelit.ino file, and make sure to include the necessary .cpp and .h files.

# MIT License

Copyright (c) 2024 andytrix

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
