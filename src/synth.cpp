#include "synth.h"

Synth::Synth(AudioSynthWaveform* waveform1,
	     AudioSynthWaveform* waveform2,
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

void Synth::oscPlay(byte note) {
  waveform1->frequency(note);  
  waveform2->frequency(note*2);

  waveform1->amplitude(0.75);
  waveform2->amplitude(0.7);
  envelope->noteOn();
}

// Synth::~Synth() {
//   delete waveform1;
//   delete waveform2;
// }
