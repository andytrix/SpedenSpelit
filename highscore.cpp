#include "highscore.h" // Highscore management

////////// INITIALIZE THE HIGH SCORE //////////
Highscore::Highscore() {
  // We can initialize the highscore to 0 if there is no value in the EEPROM
  if (EEPROM.read(highscoreAddress) == 0xFF) {
    setHighscore(0); // Set the highscore to 0
  }
}

////////// SAVE THE HIGH SCORE //////////
void Highscore::setHighscore(int newScore) {
  // Save the highscore to two EEPROM addresses (2 bytes)
  EEPROM.update(highscoreAddress, newScore & 0xFF);             // Lower byte
  EEPROM.update(highscoreAddress + 1, (newScore >> 8) & 0xFF);  // Upper byte
}

////////// READ THE HIGH SCORE FROM EEPROM MEMORY //////////
int Highscore::getHighscore() {
  // Read the highscore from two EEPROM addresses
  int lowerByte = EEPROM.read(highscoreAddress); // Read the lower byte
  int upperByte = EEPROM.read(highscoreAddress + 1); // Read the upper byte
  // Combine the upper and lower bytes into a 16-bit number and return the highscore
  return (upperByte << 8) | lowerByte; // Shift the upper byte 8 bits to the left and combine with the lower byte
}
