#include <xc.inc>

psect dividefunc, local, class=CODE, reloc=2 ; PIC18

global _divide
_divide:
	nop
	clrf WREG
	movlw 0x08
	movwf TRISA
	movff 0x01, LATD ;dividend Q
	movff 0x03, LATC ;divisor N
	clrf TRISC ;R
	rlcf LATD, F
	rlcf TRISC, F
    loop:
	bcf STATUS, 4
	movf LATC, W
	subwf TRISC, F
	bn negative
	rlcf LATD, F
	rlcf TRISC, F
	bsf LATD, 0
	goto next
    negative:
	addwf TRISC, F
	rlcf LATD, F
	rlcf TRISC, F
	bcf LATD, 0
    next:
	decfsz TRISA, F
	goto loop
	rrcf TRISC, F
	movff LATD, 0x002
	movff TRISC, 0x001
	return