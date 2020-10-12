LIST p=18f4520
#include <p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00

Initial:
    MOVLF macro literal, reg
	movlw literal
	movwf reg, 0
	endm
    ADDFFF macro f1, f2, f_res
	clrf WREG
	addwf f1, 0
	addwf f2, 0
	movwf f_res
	endm
	
start:
    nop
    MOVLF 0x6, TRISE
    clrf TRISA
    MOVLF 0x1, TRISB
    
    rcall fib
    rcall finish

fib:
    ADDFFF TRISA, TRISB, TRISC
    movff TRISB, TRISA
    movff TRISC, TRISB
    decf TRISE
    bz fib_end
    MOVLF 0x10, PCL
fib_end:
    movff TRISA, 0x12
    return
    
finish:
    end
