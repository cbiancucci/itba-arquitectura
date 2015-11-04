global outb
global inb
global playsound

%define MIDI_CONTROL_PORT 0331h
%define MIDI_DATA_PORT 0330h
%define MIDI_UART_MODE 3Fh
%define MIDI_PIANO_INSTRUMENT 93h

outb:
		mov 		rax,	rsi
		mov 		rdx,	rdi

		;int 01h

		out 		dx,		al
		ret

inb:
		mov 		rdx, 	rdi
		xor 		rax,	rax
		;int 01h

		in  		al, 	dx
		ret

playsound:
    call setup_midi
    mov ch, 60;             default octave(0)

    call get_pitch
    call play_note

;--------------------------------------------------
; Plays a note
;
; IN: AL, CH = pitch, (octave * 12) + 60
; OUT: NONE
; ERR: NONE
; REG: AL

play_note:
    add al, ch;             apply the octave
    out dx, al;             DX will already contain MIDI_DATA_PORT from the setup_midi function

    mov al, 7Fh;            note duration
    out dx, al

    ret

;--------------------------------------------------
; Based on input, returns a pitch to be played
;
; IN: AL = key code
; OUT: AL, BH, CH = pitch, 2 if no pitch to be played, (octave * 12) + 60
; ERR: NONE
; REG: preserved

get_pitch:
    mov al, 0
    ret

;--------------------------------------------------
; Set's up the MIDI ports for use
;
; IN: NONE
; OUT: NONE
; ERR: NONE
; REG: DX

setup_midi:
    push ax

    mov dx, MIDI_CONTROL_PORT
    mov al, MIDI_UART_MODE; play notes as soon as they are recieved
    out dx, al

    mov dx, MIDI_DATA_PORT
    mov al, MIDI_PIANO_INSTRUMENT
    out dx, al

    pop ax
    ret
