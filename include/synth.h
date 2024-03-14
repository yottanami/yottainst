#ifndef SYNTH_H
#define SYNTH_H
#include <Audio.h>

class Synth {
public:
    Synth(
	  AudioSynthWaveform* waveform1,
	  AudioSynthWaveform* waveform2,
	  AudioEffectEnvelope* envelope
	  );
    void setup();
    void oscPlay(byte note);

private:
    AudioSynthWaveform* waveform1;
    AudioSynthWaveform* waveform2;
    AudioEffectEnvelope* envelope;
};

#endif // SYNTH_H
