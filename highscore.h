#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <EEPROM.h> // EEPROM memory for storage

class Highscore {
public:
  Highscore(); // Initializes the Highscore object
  void setHighscore(int newScore); // Sets a new highscore
  int getHighscore(); // Returns the stored highscore from EEPROM
private:
  const int highscoreAddress = 0; // EEPROM address where the highscore is stored
};

#endif
