#ifndef PLAY_MODE_H
#define PLAY_MODE_H
#include <Audio.h>
#include "synth.h"

class PlayMode {
public:  
  PlayMode();
  void setup();
  void loop();
  void setSynth(Synth& synth);
  static void printBytes(const byte *data, unsigned int size);
  
private:
  static Synth* synth;
  static void myNoteOn(byte channel, byte note, byte velocity);
  static void myNoteOff(byte channel, byte note, byte velocity);
  static void myControlChange(byte channel, byte control, byte value);
  static void myProgramChange(byte channel, byte program);
  static void mySystemExclusive(byte *array, unsigned size);
  static void myRealTimeSystem(byte realtimebyte);
  static void myStart();
  static void myStop();
  static void myContinue();
  static void myClock();
  static void myActiveSensing();
  static void mySystemReset();
  static void myAfterTouchPoly(byte channel, byte note, byte pressure);
  static void myAfterTouchChannel(byte channel, byte pressure);
  static void myPitchChange(byte channel, int pitch);
  static void mySongPosition(uint16_t beats);
  static void mySongSelect(byte songnumber);
  static void myTuneRequest();
  static void myTimeCodeQuarterFrame(byte data);
  static void mySystemExclusiveChunk(const byte *data, uint16_t length, bool last);
};

extern PlayMode play_mode;

#endif
