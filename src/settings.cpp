#include "settings.h"

// Define the static variable instance
Settings* Settings::instance = nullptr;

// Implement other member functions of the Settings class if necessary
Settings* Settings::getInstance() {
    if (!instance) {
        // Create the instance if it doesn't exist
        instance = new Settings();
        // Set default mode (optional)
        // instance->mode = Mode::SYNTHESIZER;
    }
    return instance;
}

Mode Settings::getMode() const {
    return mode;
}

void Settings::setMode(Mode newMode) {
    mode = newMode;
}

Synth* Settings::getActiveSynth() {
  return activeSynth;
}

void Settings::setActiveSynth(Synth* synth) {
  activeSynth = synth;
		
}

Settings::~Settings() {
    delete instance;
}
