#ifndef SYNTH_H
#define SYNTH_H
#include <Audio.h>

class Synth {
public:
  Synth(
	AudioSynthWaveform* waveform1,
	AudioSynthWaveform* waveform2,
	AudioSynthNoisePink* pink,
	AudioFilterStateVariable* filter,
	AudioEffectEnvelope* envelope
	);
  void setup();
  void oscPlay(byte note);  
  void oscStop();
  void oscSet();
  void loop();
  void keyBuff(byte note, bool playNote);
  void onNoteOn(byte channel, byte note, byte velocity);
  void onNoteOff(byte channel, byte note, byte velocity);

private:
  AudioSynthWaveform* waveform1;
  AudioSynthWaveform* waveform2;
  AudioSynthNoisePink* pink;
  AudioEffectEnvelope* envelope;
  AudioFilterStateVariable* filter;
  void LFOupdate(bool retrig, byte mode, float FILtop, float FILbottom);
};

#endif // SYNTH_H
