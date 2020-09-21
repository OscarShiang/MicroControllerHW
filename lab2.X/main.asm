LIST p=18f4520
#include <p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00
    
Initial:
    ; ********************************
start:
    nop
    lfsr FSR1, 0x100
    movlw 0x00
   
loop:
    movwf INDF1
    addlw 1
    btfss POSTINC1, 3
    goto loop
    
    lfsr FSR1, 0x100
    lfsr FSR2, 0x110
    movlw 0x00
    
sum:
    addwf INDF1, 0
    movwf POSTINC2
    btfss POSTINC1, 3
    goto sum
    
end