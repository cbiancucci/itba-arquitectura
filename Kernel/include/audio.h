
#ifndef AUDIO_HEADER
#define AUDIO_HEADER

#include <stdint.h>
#include <io.h>

void play_sound(uint32_t nFrequence);
void mute_sound();
void audio_stop();
void audio_beep();

#endif
