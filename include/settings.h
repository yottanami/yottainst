#ifndef SETTINGS_H
#define SETTINGS_H

#include "synth.h"


enum class Mode {  
    SEQUENCER,
    ARPEGGIATOR,
    PLAY
};

class Settings {
public:
  // Static method to access the single instance
  static Settings* getInstance();

  // Method to get the current mode
  Mode getMode() const;
  
  // Method to update the mode
  void setMode(Mode newMode);

  Synth* getActiveSynth();
  

  void setActiveSynth(Synth* synth);

  // Destructor to clean up resources
  ~Settings();
  
private:
    // Private constructor to prevent external instantiation
    Settings() {}

    // Static instance variable to hold the single instance
    static Settings* instance;

    // Current mode setting
    Mode mode;

  Synth* activeSynth;

};

#endif
