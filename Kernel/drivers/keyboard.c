#include <keyboard.h>
#include <enums.h>

static kb_layout layout = KB_ENG;

static kb_status status = {FALSE,FALSE,FALSE};

code kb_codes[2][60] = {
	{ // ENG
	{0x02,'1','!'},
	{0x03,'2','@'}
	},{ // SPA
	{0x02,'1','!'},
	{0x03,'2','@'}
	}
};

void keyboard_handler(uint64_t s) {

}
