;LIST p=18f4520
#include<p18f4520.inc>
    CONFIG OSC = INTIO67
    CONFIG WDT = OFF
    CONFIG LVP = OFF

L1 EQU 0X14
L2 EQU 0x15

DELAY MACRO num1, num2
    local LOOP1
    local LOOP2
    movlw num2 ;1
    movwf L2 ;1
    LOOP2:
	movlw num1 ;1
	movwf L1 ;1
    LOOP1:
	nop ;1
	nop ;1
	nop ;1
	nop ;1
	nop ;1
	nop ;1
	nop ;1
	decfsz L1, 1 ;1
	goto LOOP1 ;2
	decfsz L2, 1 ;1
	goto LOOP2 ;2
  endm
	org 0x0

start:
    clrf WREG
    clrf TRISD
    clrf 0x005
    clrf LATD

    clrf PORTA
    movlw 0x10
    movwf TRISA
    movlw 0x00

state0:
    btfsc PORTA, 4
    goto state0
    goto state1

state1:
    movwf LATD
    rlcf LATD, 1
    movlw 1
    addwf LATD, 1
    movlw 0x10
    cpfslt LATD
    clrf LATD

    DELAY d'50', d'250'
    movf LATD, 0
    clrf LATD

    goto state0

  end