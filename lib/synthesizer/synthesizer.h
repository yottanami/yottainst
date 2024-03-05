#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

class Synthesizer {
public:
  Synthesizer();
  void setup();

private:
  static void onControlChange(byte channel, byte control, byte value);
};

extern Synthesizer synthesizer;

#endif
