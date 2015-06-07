
#ifndef VIDEO_HEADER
#define VIDEO_HEADER

#include <stdint.h>

#define SCREEN_START ((uint16_t*)0xB8000)

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void video_clear_screen();

#endif
