#include "play_mode.h"
#include <Audio.h>

#include <USBHost_t36.h>
#include <EEPROM.h>
#include "settings.h"
#include "audio_setup.h"
#include "lead_synth.h"
Synth* PlayMode::synth = nullptr; 

PlayMode::PlayMode() {
  // Constructor

}


USBHost myusb;
USBHub hub1(myusb);
//USBHub hub2(myusb);
MIDIDevice midi1(myusb);

void PlayMode::setSynth(Synth& synth){
  //this->synth = &synth;
  // LeadSynth lead_synth;
  // lead_synth.setup();
  
   this->synth = &synth;
}

void PlayMode::setup() {

  // Wait 1.5 seconds before turning on USB Host.  If connected USB devices
  // use too much power, Teensy at least completes USB enumeration, which
  // makes isolating the power issue easier.
  delay(1500);
  Serial.println("USB Host InputFunctions example");

  delay(10);
  myusb.begin();

  
  midi1.setHandleNoteOn(myNoteOn);
  //midi1.setHandleNoteOff(myNoteOff);
  //midi1.setHandleAfterTouchPoly(myAfterTouchPoly);
  //midi1.setHandleControlChange(myControlChange);
  //midi1.setHandleProgramChange(myProgramChange);
  //midi1.setHandleAfterTouchChannel(myAfterTouchChannel);
  //midi1.setHandlePitchChange(myPitchChange);
  // Only one of these System Exclusive handlers will actually be
  // used.  See the comments below for the difference between them.
  //midi1.setHandleSystemExclusive(mySystemExclusiveChunk);
  //midi1.setHandleSystemExclusive(mySystemExclusive); 
  // midi1.setHandleTimeCodeQuarterFrame(myTimeCodeQuarterFrame);
  // midi1.setHandleSongPosition(mySongPosition);
  // midi1.setHandleSongSelect(mySongSelect);
  // midi1.setHandleTuneRequest(myTuneRequest);
  // midi1.setHandleClock(myClock);
  // midi1.setHandleStart(myStart);
  // midi1.setHandleContinue(myContinue);
  // midi1.setHandleStop(myStop);
  // midi1.setHandleActiveSensing(myActiveSensing);
  // midi1.setHandleSystemReset(mySystemReset);
  // This generic System Real Time handler is only used if the
  // more specific ones are not set.
  //midi1.setHandleRealTimeSystem(myRealTimeSystem);
  Serial.println("USB Host InputFunctions setup done");
  //active_synth = settings->getActiveSynth();

  Serial.println("Play mode setup done");
}

void PlayMode::loop() {
  // The handler functions are called when midi1 reads data.  They
  // will not be called automatically.  You must call midi1.read()
  // regularly from loop() for midi1 to actually read incoming
  // data and run the handler functions as messages arrive.
  myusb.Task();
  midi1.read();
  // ignore incoming messages
}


void PlayMode::myNoteOn(byte channel, byte note, byte velocity) {
  // When a USB device with multiple virtual cables is used,
  // midi1.getCable() can be used to read which of the virtual
  // MIDI cables received this message.
      
  Serial.print("Note On, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);

  if (synth != nullptr) {
    Serial.println("Playing note");
      synth->oscPlay(40);
      Serial.println("Note played");
    }
  
  // if(settings->getMode() == Mode::PLAY){
  //   Serial.println("PLAY MODE");
  // }else if(settings->getMode() == Mode::SEQUENCER){
  //   Serial.println("SEQUENCER MODE");
  // } else if(settings->getMode() == Mode::ARPEGGIATOR){
  //   Serial.println("ARPEGGIATOR MODE");
  // } else {
  //   Serial.println("UNKNOWN MODE");
  // }

  // if(settings->getActiveSynth() != nullptr){
  //   Serial.println("Playing note");

  //   Synth* active_synth = settings->getActiveSynth();
  //   // active_synth->onNoteOn(channel, note, velocity);
  //   if (active_synth == nullptr){
  // 			Serial.println("Active synth is null");
  // 		}else {
  //     active_synth->oscPlay(40);
  //   //    Serial.println(active_synth->); // ;
  //   Serial.println("Note played");
  //   }
  // }else{
  //   Serial.println("No active synth");
  // }
  //active_synth->oscPlay(40);
  //Synth* active_synth = settings->getActiveSynth();
  //active_synth->oscPlay(40);
  
  
  
}

void PlayMode::myNoteOff(byte channel, byte note, byte velocity) {
  synth->onNoteOff(channel, note, velocity);
  Serial.print("Note Off, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}

void PlayMode:: myAfterTouchPoly(byte channel, byte note, byte velocity) {
  Serial.print("AfterTouch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", note=");
  Serial.print(note, DEC);
  Serial.print(", velocity=");
  Serial.println(velocity, DEC);
}

void PlayMode::myControlChange(byte channel, byte control, byte value) {
  Serial.print("Control Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", control=");
  Serial.print(control, DEC);
  Serial.print(", value=");
  Serial.println(value, DEC);
}

void PlayMode::myProgramChange(byte channel, byte program) {
  Serial.print("Program Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", program=");
  Serial.println(program, DEC);
}

void PlayMode::myAfterTouchChannel(byte channel, byte pressure) {
  Serial.print("After Touch, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pressure=");
  Serial.println(pressure, DEC);
}

void PlayMode::myPitchChange(byte channel, int pitch) {
  Serial.print("Pitch Change, ch=");
  Serial.print(channel, DEC);
  Serial.print(", pitch=");
  Serial.println(pitch, DEC);
}


// This 3-input System Exclusive function is more complex, but allows you to
// process very large messages which do not fully fit within the midi1's
// internal buffer.  Large messages are given to you in chunks, with the
// 3rd parameter to tell you which is the last chunk.  This function is
// a Teensy extension, not available in the Arduino MIDI library.
//
void PlayMode::mySystemExclusiveChunk(const byte *data, uint16_t length, bool last) {
  Serial.print("SysEx Message: ");
  printBytes(data, length);
  if (last) {
    Serial.println(" (end)");
  } else {
    Serial.println(" (to be continued)");
  }
}

// This simpler 2-input System Exclusive function can only receive messages
// up to the size of the internal buffer.  Larger messages are truncated, with
// no way to receive the data which did not fit in the buffer.  If both types
// of SysEx functions are set, the 3-input version will be called by midi1.
//
void PlayMode::mySystemExclusive(byte *data, unsigned int length) {
  Serial.print("SysEx Message: ");
  printBytes(data, length);
  Serial.println();
}

void PlayMode::myTimeCodeQuarterFrame(byte data) {
  static char SMPTE[8]={'0','0','0','0','0','0','0','0'};
  static byte fps=0;
  byte index = data >> 4;
  byte number = data & 15;
  if (index == 7) {
    fps = (number >> 1) & 3;
    number = number & 1;
  }
  if (index < 8 || number < 10) {
    SMPTE[index] = number + '0';
    Serial.print("TimeCode: ");  // perhaps only print when index == 7
    Serial.print(SMPTE[7]);
    Serial.print(SMPTE[6]);
    Serial.print(':');
    Serial.print(SMPTE[5]);
    Serial.print(SMPTE[4]);
    Serial.print(':');
    Serial.print(SMPTE[3]);
    Serial.print(SMPTE[2]);
    Serial.print('.');
    Serial.print(SMPTE[1]);  // perhaps add 2 to compensate for MIDI latency?
    Serial.print(SMPTE[0]);
    switch (fps) {
      case 0: Serial.println(" 24 fps"); break;
      case 1: Serial.println(" 25 fps"); break;
      case 2: Serial.println(" 29.97 fps"); break;
      case 3: Serial.println(" 30 fps"); break;
    }
  } else {
    Serial.print("TimeCode: invalid data = ");
    Serial.println(data, HEX);
  }
}

void PlayMode::mySongPosition(uint16_t beats) {
  Serial.print("Song Position, beat=");
  Serial.println(beats);
}

void PlayMode::mySongSelect(byte songNumber) {
  Serial.print("Song Select, song=");
  Serial.println(songNumber, DEC);
}

void PlayMode::myTuneRequest() {
  Serial.println("Tune Request");
}

void PlayMode::myClock() {
  Serial.println("Clock");
}

void PlayMode::myStart() {
  Serial.println("Start");
}

void PlayMode::myContinue() {
  Serial.println("Continue");
}

void PlayMode::myStop() {
  Serial.println("Stop");
}

void PlayMode::myActiveSensing() {
  Serial.println("Actvice Sensing");
}

void PlayMode::mySystemReset() {
  Serial.println("System Reset");
}

void PlayMode::myRealTimeSystem(uint8_t realtimebyte) {
  Serial.print("Real Time Message, code=");
  Serial.println(realtimebyte, HEX);
}



void PlayMode::printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}


PlayMode play_mode = PlayMode();
