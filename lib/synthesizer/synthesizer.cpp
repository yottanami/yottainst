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
AudioEffectEnvelope      envelope1;      //xy=615,372
AudioOutputI2S           i2s1;           //xy=806,381
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(pink1, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, envelope1);
AudioConnection          patchCord5(envelope1, 0, i2s1, 0);
AudioConnection          patchCord6(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=448,517
// GUItool: end automatically generated code


// GLOBAL VARIABLES 
const byte BUFFER = 8; //Size of keyboard buffer
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911,  6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

byte globalNote = 0;
byte globalVelocity = 0;
int Synthesizer::octave = 0;
const float DIV127 = (1.0 / 127.0);


Synthesizer::Synthesizer(){
}

void Synthesizer::setup(){
  AudioMemory(20);
  usbMIDI.setHandleControlChange(Synthesizer::onControlChange);
  usbMIDI.setHandleNoteOn(Synthesizer::onNoteOn);
  usbMIDI.setHandleNoteOff(Synthesizer::onNoteOff);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  
  waveform1.begin(WAVEFORM_SAWTOOTH);
  waveform1.amplitude(0.75);
  waveform1.frequency(82.41);
  waveform1.pulseWidth(0.15);

  waveform2.begin(WAVEFORM_SAWTOOTH);
  waveform2.amplitude(0.75);
  waveform2.frequency(123);
  waveform2.pulseWidth(0.15);
  
  pink1.amplitude(1.0);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);

  envelope1.attack(0);
  envelope1.decay(0);
  envelope1.sustain(1);
  envelope1.release(500);
}

void Synthesizer::onControlChange(byte channel, byte control, byte value){
  Serial.print("Control Change: ");
  
  switch (control) {
  case 100:
    mixer1.gain(0, (value * DIV127));
    break;

  case 101:
    mixer1.gain(1, (value * DIV127));
    break;

  case 102:
    mixer1.gain(2, (value * DIV127));
    break;

  case 103:
    switch (value) {
    case 0:
      Synthesizer::octave = 24;
      break;
    case 1:
      Synthesizer::octave = 12;
      break;
    case 2:
      Synthesizer::octave = 0;
      break;
    case 3:
      Synthesizer::octave = -12;
      break;
    case 4:
      Synthesizer::octave = -24;
      break;
    }
    break;

  case 104:
    envelope1.attack(3000 * (value * DIV127));
    break;

  case 105:
    envelope1.decay(3000 * (value * DIV127));
    break;

  case 106:
    envelope1.sustain(value * DIV127);
    break;

  case 107:
    envelope1.release(3000 * (value * DIV127));
    break;
  }
}

void Synthesizer::onNoteOn(byte channel, byte note, byte velocity){
  if(note > 23 && note < 108){
    globalNote = note;
    globalVelocity = velocity;
    Synthesizer::keyBuff(note, true);
  }
}

void Synthesizer::onNoteOff(byte channel, byte note, byte velocity){
  if(note > 23 && note < 108){
    Synthesizer::keyBuff(note, false);
  }
}

void Synthesizer::keyBuff(byte note, bool playNote){
  static byte buff[BUFFER];
  // How many notes are in the buffer
  static byte buffSize = 0;

  // Add note to buffer
  if(playNote == true && buffSize < BUFFER){
    Synthesizer::oscPlay(note);
    buff[buffSize] = note;
    buffSize++;
    return;
  }
  // Remove note from buffer
  else if(playNote == false && buffSize != 0){
    for(byte found = 0; found < buffSize; found++){
      if(buff[found] == note){
	for(byte i = found; i < (buffSize - 1); i++){
	  buff[i] = buff[i + 1];
	}
	buffSize--;
	buff[buffSize] = 255;
	if (buffSize != 0){
	  Synthesizer::oscPlay(buff[buffSize - 1]);
	  return;	
	}else {    
	  Synthesizer::oscStop();
	  return;
	}
      }
    }
  }
}

void Synthesizer::oscPlay(byte note) {
  waveform1.frequency(noteFreqs[note]);
  waveform2.frequency(noteFreqs[note + Synthesizer::octave]);
  float velo = (globalVelocity * DIV127);
  waveform1.amplitude(velo);
  waveform2.amplitude(velo);
  pink1.amplitude(velo);

  envelope1.noteOn();
}

void Synthesizer::oscStop() {
  envelope1.noteOff();
}    

Synthesizer synthesizer = Synthesizer();
