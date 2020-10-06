LIST p=18f4520
#include <p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    org 0x00
    
start:
   ; set up TRISB
   movlw 0x08
   movwf TRISB
   
   ; set up TRISC
   movlw 0x0b
   movwf TRISC
   
   clrf TRISA
   
   movlw 0x04
   movwf TRISD
   
   nop
   
mul:
   clrf WREG
   btfsc TRISC, 0
   addwf TRISB, 0
   addwf TRISA
   
   rrncf TRISC, 1
   rlncf TRISB, 1
   decf TRISD
   bnz mul
    
end