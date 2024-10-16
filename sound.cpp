#include "sound.h" // Sound effects

#define SPEAKER_PIN 6 // Speaker pin

////////// NOTE FREQUENCIES IN MICROSECONDS //////////
int BassTab[] = {3000, 1702, 1516, 1431, 1275, 1136, 1012}; // Bass notes 1~7

////////// SPEAKER INITIALIZATION FUNCTION //////////
void initializeSpeaker(void) {
    pinMode(SPEAKER_PIN, OUTPUT); // Set the speaker pin as output
    digitalWrite(SPEAKER_PIN, LOW); // Ensure the speaker is off initially
}

////////// PLAY SOUND EFFECT //////////
void sound(uint8_t note_index) {
    for (int i = 0; i < 100; i++) { // Repeat the sound cycle 100 times
        digitalWrite(SPEAKER_PIN, HIGH); // Turn the speaker on
        delayMicroseconds(BassTab[note_index]); // Wait based on the frequency from the table
        digitalWrite(SPEAKER_PIN, LOW); // Turn the speaker off
        delayMicroseconds(BassTab[note_index]); // Wait based on the frequency from the table
    }
}
