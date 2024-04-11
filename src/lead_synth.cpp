// #include "lead_synth.h"
// #include "audio_setup.h"

// Synth* LeadSynth::instance = nullptr;

// LeadSynth* LeaSynth::getInstance() {
//   if (!instance) {
//     instance = new LeadSynth();
//   }
//   return instance;
// }

// //LeadSynth::LeadSynth() {
//   // waveform1 = &lead_waveform1;
//   // waveform2 = &lead_waveform2;
//   // pink = &lead_pink;
//   // envelope = &lead_envelope;
//   // filter = &lead_filter;  
// //}

// void LeadSynth::setup() {
//   Serial.println("LeadSynth setup");
//   lead_waveform1.begin(WAVEFORM_SAWTOOTH);
//   lead_waveform1.pulseWidth(0.15);
//   lead_waveform1.amplitude(1.0);
// }

// void LeadSynth::oscPlay(byte note) {
//   Serial.println("LeadSynth oscPlay");
//    lead_waveform1.frequency(50);
//    lead_waveform1.amplitude(1.0);
//    lead_envelope.noteOn();

// }

// void LeadSynth::oscStop() {
//   Serial.println("LeadSynth oscStop");
//   lead_envelope.noteOff();
// }

// LeadSynth::~LeadSynth() {
// 	delete instance;
// }
