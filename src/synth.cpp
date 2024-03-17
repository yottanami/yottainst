#include "synth.h"
#include "audio_setup.h"


// Constants
const byte BUFFER = 8;
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911,  6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
const float DIV127 = (1.0 / 127.0);


// TODO: check if could be defined as const
float bendFactor = 1.0;
float LFOpitch = 1.0;
byte velocity = 127;
float FILfactor = 1;
byte globalNote = 0;
int FILfreq =  10000;


// Adjustable parameters
int octave = 1;
float detuneFactor = 1.0;
float LFOdepth = 0.0;
byte LFOmodeSelect = 0;
unsigned int LFOspeed = 2000;
// waveforms types



Synth::Synth(AudioSynthWaveform* waveform1,
	     AudioSynthWaveform* waveform2,
	     AudioSynthNoisePink* pink,
	     AudioFilterStateVariable* filter,
	     AudioEffectEnvelope* envelope) {
  this->waveform1 = waveform1;
  this->waveform2 = waveform2;
  this->envelope = envelope;
}

void Synth::setup() {
  waveform1->begin(WAVEFORM_SAWTOOTH);
  waveform1->pulseWidth(0.15);

  waveform2->begin(WAVEFORM_SINE);
  waveform2->pulseWidth(0.15);  
  
}

void Synth::loop() {
  LFOupdate(false, LFOmodeSelect, FILfactor, LFOdepth);
}

void Synth::oscPlay(byte note) {
  waveform1->frequency(noteFreqs[note] * bendFactor);
  waveform2->frequency(noteFreqs[note + octave] * detuneFactor * bendFactor * LFOpitch);
  float velo = (velocity * DIV127);
  waveform1->amplitude(velo);
  waveform2->amplitude(velo);
  pink->amplitude(velo);

  envelope->noteOn();
}

void Synth::oscStop() {
  envelope->noteOff();
}

void Synth::oscSet() {
  waveform1->frequency(noteFreqs[globalNote] * bendFactor);
 waveform2->frequency(noteFreqs[globalNote + octave] * detuneFactor * bendFactor * LFOpitch);  
}

void Synth::onNoteOn(byte channel, byte note, byte vel){
  if(note > 23 && note < 108){
    globalNote = note;
    velocity = vel;
    keyBuff(note, true);
    LFOupdate(true, LFOmodeSelect, FILfactor, LFOdepth);
  }
}

void Synth::onNoteOff(byte channel, byte note, byte velocity){
  if(note > 23 && note < 108){
    keyBuff(note, false);
  }
}

void Synth::keyBuff(byte note, bool playNote){
  static byte buff[BUFFER];
  // How many notes are in the buffer
  static byte buffSize = 0;

  // Add note to buffer
  if(playNote == true && buffSize < BUFFER){
    oscPlay(note);
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
	  oscPlay(buff[buffSize - 1]);
	  return;	
	}else {    
	  oscStop();
	  return;
	}
      }
    }
  }
}

void Synth::LFOupdate(bool retrig, byte mode, float FILtop, float FILbottom) {
  static float LFO = 0;
  static unsigned long LFOtime = 0;
  static bool LFOdirection = false;
  unsigned long currentMicros = micros();
  static bool LFOstop = false;
  static float LFOrange = 0;
  static byte oldMode = 0;
  static bool retriggered = false;

  if (retrig == true) retriggered = true;


  if (currentMicros - LFOtime >= LFOspeed) {
    LFOtime = currentMicros;

    if (mode != oldMode) {
      if (mode == 0 || mode == 8) {
        LFOpitch = 1;
	oscSet();
        filter->frequency(FILfreq);
      }
      else if (mode >= 1 || mode <= 7) {
        LFOpitch = 1;
        oscSet();
      }
      else if (mode >= 9 || mode <= 13) {
        filter->frequency(FILfreq);
      }
      oldMode = mode;
    }

    LFOrange = FILtop - FILbottom;
    if (LFOrange < 0) LFOrange = 0;

    // LFO Modes
    switch (mode) {

    case 0: //Filter OFF
      return;
      break;
    case 1: //Filter FREE
      filter->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
      break;
    case 2: //Filter DOWN
      if (retriggered == true) {
	LFOdirection = true;
	LFO = 1.0;
      }
      filter->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
      break;
    case 3: //Filter UP
      if (retriggered == true) {
	LFOdirection = false;
	LFO = 0;
      }
      filter->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
      break;
    case 4: //Filter 1-DN
      if (retriggered == true) {
	LFOstop = false;
	LFOdirection = true;
	LFO = 1.0;
      }
      if (LFOstop == false) filter->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
      break;
    case 5: //Filter 1-UP
      if (retriggered == true) {
	LFOstop = false;
	LFOdirection = false;
	LFO = 0;
      }
      if (LFOstop == false) filter->frequency(10000 * ((LFOrange * LFO) + LFOdepth));
      break;
    case 8: //Pitch OFF
      return;
      break;
    case 9: //Pitch FREE
      LFOpitch = (LFO * LFOdepth) + 1;
      oscSet();
      break;
    case 10: //Pitch DOWN
      if (retriggered == true) {
	LFOdirection = true;
	LFO = 1.0;
      }
      LFOpitch = (LFO * LFOdepth) + 1;
      oscSet();
      break;
    case 11: //Pitch UP
      if (retriggered == true) {
	LFOdirection = false;
	LFO = 0;
      }
      LFOpitch = (LFO * LFOdepth) + 1;
      oscSet();
      break;
    case 12: //Pitch 1-DN
      if (retriggered == true) {
	LFOstop = false;
	LFOdirection = true;
	LFO = 1.0;
      }
      if (LFOstop == false) {
	LFOpitch = (LFO * LFOdepth) + 1;
	oscSet();
      }
      break;
    case 13: //Pitch 1-UP
      if (retriggered == true) {
	LFOstop = false;
	LFOdirection = false;
	LFO = 0;
      }
      if (LFOstop == false) {
	LFOpitch = (LFO * LFOdepth) + 1;
	oscSet();
      }
      break;
    }

    retriggered = false;

    // Update LFO
    if (LFOdirection == false) { //UP
      LFO = (LFO + 0.01);
      if (LFO >= 1) {
        LFOdirection = true;
        LFOstop = true;
      }
    }

    if (LFOdirection == true) { //Down
      LFO = (LFO - 0.01);
      if (LFO <= 0) {
        LFOdirection = false;
        LFOstop = true;
      }
    }
  }
}
