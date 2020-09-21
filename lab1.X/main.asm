LIST p=18f4520
#include <p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00
    
Initial:
    ; ********************************
    
start:
    clrf WREG
    clrf TRISC
    
    movlw 0xf
    addwf TRISC, 1
    
    clrf WREG
    
loop:
    addwf TRISC, 0
    decfsz TRISC, 1
    goto loop
    
end


