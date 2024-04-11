#ifndef SYNTH_H
#define SYNTH_H
#include <memory>
#include <Audio.h>

class Synth {
public:
  static Synth* getInstance();
  void setup();
  void oscPlay(byte note);  
  void oscStop();
  void oscSet();
  void loop();
  void keyBuff(byte note, bool playNote);
  void onNoteOn(byte channel, byte note, byte velocity);
  void onNoteOff(byte channel, byte note, byte velocity);  
  ~Synth();

private:
  Synth(AudioSynthWaveform waveform1,
        AudioSynthWaveform waveform2,
        AudioSynthNoisePink pink,
        AudioEffectEnvelope envelope,
        AudioFilterStateVariable filter);
  
  AudioSynthWaveform waveform1;
  AudioSynthWaveform waveform2;
  AudioSynthNoisePink pink;
  AudioEffectEnvelope envelope;
  AudioFilterStateVariable filter;
  
  static Synth* instance;
  void LFOupdate(bool retrig, byte mode, float FILtop, float FILbottom);

};

#endif // SYNTH_H
