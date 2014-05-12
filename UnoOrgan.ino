#include <MozziGuts.h>
#include <Smooth.h>
#include <mozzi_midi.h>
#include <Oscil.h> // oscillator template
#include <tables/cos2048_int8.h>
#define NUM_TONES 12
#define CONTROL_RATE 256

Oscil <COS2048_NUM_CELLS, AUDIO_RATE> tones[NUM_TONES];
bool toneEnabled[NUM_TONES];
int totalTone = 0;
int tonesPlaying = 0;
int count = 1;
Smooth <int> smoother(0.9f);
int enabledTones = 0;
void setup()
{
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  startMozzi(CONTROL_RATE);
  for(int i = 0; i < NUM_TONES; i++)
  {
    tones[i].setTable(COS2048_DATA);
    tones[i].setFreq(GetNoteFreq(i));
    toneEnabled[i] = false;
  }
}


void updateControl()
{
  toneEnabled[0] = digitalRead(1);
  toneEnabled[1] = digitalRead(2);
  toneEnabled[2] = digitalRead(3);
  toneEnabled[3] = digitalRead(4);
  toneEnabled[4] = digitalRead(5);
  toneEnabled[5] = digitalRead(6);
  toneEnabled[6] = digitalRead(7);
  toneEnabled[7] = digitalRead(8);
  toneEnabled[8] = digitalRead(10);
  toneEnabled[9] = digitalRead(11);
  toneEnabled[10] = digitalRead(12);
  toneEnabled[11] = digitalRead(13);
}


int updateAudio()
{
  totalTone = 0;
  int c = 0;
  for(int i = 0; i < NUM_TONES; i++)
  {
    if(toneEnabled[i] && c < 4)
    {
        totalTone += (tones[i].next()>>2);
        c++;
    }
  }
  
  return totalTone;
}


void loop()
{
  audioHook();
}

float GetNoteFreq(int semitoneOffset)
{
  return Q16n16_mtof(36 + semitoneOffset);
  return 220 * pow(1.059463, semitoneOffset);
}


