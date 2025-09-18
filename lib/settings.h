#ifndef SETTINGS_H
#define SETTINGS_H

enum class Mode {
  SYNTHESIZER,
  SEQUENCER,
  ARPEGGIATOR
};

class Settings {
private:
  // Private constructor to prevent external instantiation
  Settings() {}

  // Static instance variable to hold the single instance
  static Settings* instance;

  // Current mode setting
  Mode mode;

public:
  // Static method to access the single instance
  static Settings* getInstance() {
    if (!instance) {
      // Create the instance if it doesn't exist
      instance = new Settings();
      // Set default mode (optional)
      //instance->mode = Mode::SYNTHESIZER;
    }
    return instance;
  }

  // Method to get the current mode
  Mode getMode() const {
    return mode;
  }

  // Method to update the mode
  void setMode(Mode newMode) {
    mode = newMode;
  }

  // Destructor to clean up resources
  ~Settings() {
    delete instance;
  }
};

// Initialize the static instance variable to nullptr
Settings* Settings::instance = nullptr;

#endif
