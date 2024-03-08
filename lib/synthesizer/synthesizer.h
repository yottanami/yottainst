#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

class Synthesizer {
public:
  static int octave;
  
  Synthesizer();
  void setup();
  void loop();

private:
  static void onControlChange(byte channel, byte control, byte value);
  static void onNoteOn(byte channel, byte note, byte velocity);
  static void onNoteOff(byte channel, byte note, byte velocity);
  static void onPitchChange(byte channel, int pitch);
  static void keyBuff(byte note, bool on);
  static void oscPlay(byte note);
  static void oscStop();
  static void oscSet();
  static void LFOupdate(bool retrig, byte mode, float FILtop, float FILbottom);
};

extern Synthesizer synthesizer;

#endif
