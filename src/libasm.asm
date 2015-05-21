GLOBAL  _read_msw,_lidt
GLOBAL  _int_08_hand, _int_09_hand
GLOBAL	_outb, _inb, _outl, _inl
GLOBAL	_tjunction, _temp_relativa
GLOBAL  _mascaraPIC1,_mascaraPIC2,_Cli,_Sti
GLOBAL  _debug

EXTERN  int_08, int_09

SECTION .text


_Cli:
	cli			; limpia flag de interrupciones
	ret

_Sti:

	sti			; habilita interrupciones por flag
	ret

_mascaraPIC1:			; Escribe mascara del PIC 1
		push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out		21h, al
        pop     ebp
        retn

_mascaraPIC2:			; Escribe mascara del PIC 2
		push    ebp
        mov     ebp, esp
        mov     ax, [ss:ebp+8]  ; ax = mascara de 16 bits
        out		0A1h, al
        pop     ebp
        retn

_read_msw:
        smsw    ax		; Obtiene la Machine Status Word
        retn


_lidt:				; Carga el IDTR
        push    ebp
        mov     ebp, esp
        push    ebx
        mov     ebx, [ss: ebp + 6] ; ds:bx = puntero a IDTR 
		rol		ebx, 16		    	
		lidt    [ds: ebx]          ; carga IDTR
        pop     ebx
        pop     ebp
        retn

_int_08_hand:				; Handler de INT 8 ( Timer tick)
        pusha       		; Se salvan los registros       
        call    int_08
        mov		al, 20h		; Envio de EOI generico al PIC
		out		20h, al
		popa                            
        iret
        
_int_09_hand:				; Handler del teclado
		pusha				; Se guardan los registros
		mov     eax, 0h	 
		in 		al, 60h		; Se recupera el scan code
		push 	eax			
		call 	int_09			
		pop 	eax
		mov 	al, 20h		; Envio de EOI generico al PIC
		out 	20h, al
		popa				; Se recupera el estado de los registros
		iret
		
_tjunction:					; Lee la temperatura maxima del procesador
		push 	ebp
		mov 	ebp, esp
		mov 	ecx, 1A2h
		rdmsr
		ror 	eax, 16
		and 	eax, 0FFh
		mov 	esp, ebp
		pop 	ebp
		ret
		

_temp_relativa:				; Lee la diferencia entre la temperatura
		push 	ebp			; maxima y la real.
		mov 	ebp, esp
		mov 	ecx, 19Ch
		rdmsr
		ror 	eax, 16
		and 	eax, 07Fh
		mov 	esp, ebp
		pop 	ebp
		ret
		
		
_outb:
		push 	ebp
		mov		ebp, esp
		push 	ax
		push 	dx
		mov	word	dx, [ebp + 8]
		mov	word 	ax, [ebp + 12]
		out 	dx, al
		pop 	dx	
		pop		ax
		mov		esp, ebp
		pop 	ebp
		ret
		
_outl:
		push 	ebp
		mov 	ebp, esp
		mov 	dx, word[ebp+8]
		mov 	eax, dword[ebp+12]
		out 	dx, eax
		mov 	esp, ebp
		pop 	ebp
		ret
		
_inb:
		push 	ebp
		mov		ebp, esp
		push	dx
		xor 	eax, eax
		mov	word	dx, [ebp + 8]
		in		al, dx
		pop		dx
		mov		esp, ebp
		pop 	ebp
		ret

_inl:
		push	ebp
		mov 	ebp, esp
		xor		eax, eax
		mov		dx, word[ebp+8]
		in 		eax, dx
		mov 	esp, ebp
		pop 	ebp
		ret

; Debug para el BOCHS, detiene la ejecución
; Para continuar colocar en el BOCHSDBG: set $eax=0


_debug:
        push    bp
        mov     bp, sp
        push	ax
vuelve:	mov     ax, 1
        cmp	ax, 0
	jne	vuelve
	pop	ax
	pop     bp
        retn
