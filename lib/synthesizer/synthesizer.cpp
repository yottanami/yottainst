# include "Arduino.h"
//# include "settings.h"
# include "synthesizer.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=271,347
AudioOutputI2S           i2s1;           //xy=567,338
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=448,517
// GUItool: end automatically generated code
Synthesizer::Synthesizer(){
}

void Synthesizer::setup(){
  AudioMemory(20);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.5);
  waveform1.frequency(50);
  waveform1.pulseWidth(0.15);
}

Synthesizer synthesizer = Synthesizer();
