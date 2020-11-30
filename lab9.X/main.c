#include <xc.h>
#include <pic18f4520.h>

#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit 
#pragma config PWRT = OFF    // Power-up Enable bit
#pragma config BOREN = ON   // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM　Memory Code Protection bit (Data EEPROM code protection off)

void delay(int time)
{
    for (int i = 0; i < time; i++) {
        for (int j = 0; j < 150; j++) {
            /* iterates */
        }
    }
}

void main(void) {

    T2CON = 0b01111111; // pre / post -> 16 / 16
    OSCCONbits.IRCF = 0b001; // set 125k, 8us
    CCP1CONbits.CCP1M = 0b1100; // PWM on
    
    TRISC = 0;
    TRISB = 0x1;
    LATC = 0;
    LATB = 0;
    PORTB = 0;

    // 20000 = (x + 1) * 4 * 8 * 16
    // x => 38
    
    PR2 = 38;

    // 500 = [4] * 8 * 16
    // 2400 = [19] * 8 * 16

    while (1) {
        CCPR1L = 0b001; // 8 bits
        CCP1CONbits.DC1B = 0b00; // 2 bits
        
        do {
            /* iterates */
        } while (PORTB & 0x1);
        
        for (unsigned int i = 4; i <= 20; i++) {
            CCPR1L = (i >> 2) & 0xff;
            CCP1CONbits.DC1B = i & 0x3;
            delay(1);
        }
    }
    
    return;
}