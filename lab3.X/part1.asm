LIST p=18f4520
#include <p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00
    
start:
    nop
    
    ; clean up
    andlw 0x0
    andwf LATA, 1
    
    ; do operations
    iorlw 0xdf
    andlw 0x9e
    xorlw 0xff

    ; store back the result
    iorwf LATA, 1
    
    ; clean up
    andlw 0x0
    andwf LATB, 1
    
    iorlw 0x5b
    iorlw 0xc4
    xorlw 0xff
    
    ; store back
    iorwf LATB, 1
end
