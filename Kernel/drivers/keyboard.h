typedef struct {
	bool alt;
	bool shift;
	bool ctrl;

} kb_status;

typedef struct {
	char code;
	char ascii;
	char shifted;
} code;

typedef enum {
	KB_ENG,
	KB_SPA
} kb_layout;


void keyboard_handler(uint64_t s);
