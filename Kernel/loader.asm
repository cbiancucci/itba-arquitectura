global loader
extern 	main
extern 	initializeKernelBinary
extern 	keyboard_handler

loader:
	call initializeKernelBinary	
	mov rsp, rax				
	push rax
	call set_interrupt_handlers
	call init_pic
	call main
hang:
	hlt
	jmp hang

create_gate:
		push 		rdi
		push 		rax

		shl 		rdi,	4		
		stosw		
		shr 		rax, 	16
		add 		rdi,	4	
		stosw						
		shr 		rax,	16
		stosd					

		pop 		rax
		pop 		rdi

		ret

set_interrupt_handlers:

		mov 		rdi, 0x21
		mov 		rax, keyboard
		call 		create_gate

		mov 		rdi, 0x80
		mov 		rax, software_interruptions
		call		create_gate

		mov		rdi, 0x20
		mov		rax, prog_interval_timer
		call		create_gate


		ret

align 16
software_interruptions:
		push rdi
		
		pop rdi
		ret

get_params_ready:
		mov 		rdi,	rsi
		mov 		rsi,	rdx
		mov 		rdx,	rcx
		mov		rcx,	r8

		ret

prog_interval_timer:

		ret

align 16
keyboard:
		push 		rdi
		push 		rax

		xor		eax, eax

		in 		al, 0x60				

		mov 		rdi,	 rax
		call 		keyboard_handler

		ret

init_pic:
	; Enable specific interrupts
	in al, 0x21
	mov al, 11111000b		; Enable Cascade, Keyboard
	out 0x21, al

	sti				; Enable interrupts

	ret
