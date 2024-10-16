#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h> // Include core Arduino functionality

void initializeSpeaker(void);       // Initializes the speaker
void sound(uint8_t note_index);     // Plays a sound effect based on the note index

#endif
