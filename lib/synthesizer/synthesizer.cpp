# include "Arduino.h"
//# include "settings.h"
# include "synthesizer.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=258,335
AudioSynthWaveform       waveform1;      //xy=260,272
AudioSynthNoisePink      pink1;          //xy=265,391
AudioMixer4              mixer1;         //xy=464,372
AudioOutputI2S           i2s1;           //xy=637,371
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=448,517
// GUItool: end automatically generated code

Synthesizer::Synthesizer(){
}

void Synthesizer::setup(){
  AudioMemory(20);
  usbMIDI.setHandleControlChange(Synthesizer::onControlChange);  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.5);
  waveform1.frequency(50);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SQUARE);
  waveform2.amplitude(0.5);
  waveform2.frequency(50);
  waveform2.pulseWidth(0.15);

  pink1.amplitude(1.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);
}

void Synthesizer::onControlChange(byte channel, byte control, byte value){
  Serial.print("Control Change: ");
  
  switch(control){
  case 100:
    Serial.println("100");
    mixer1.gain(0, (float)value / 127.0);
    break;
  case 101:
    mixer1.gain(1, (float)value / 127.0);
    break;
  case 102:
    mixer1.gain(2, (float)value / 127.0);
    break;
  }
}

Synthesizer synthesizer = Synthesizer();
