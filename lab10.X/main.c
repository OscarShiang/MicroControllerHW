// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned int result, counter;

void __interrupt(high_priority) ISR(void)
{
    if (PIR1bits.ADIF) {
        PIR1bits.ADIF = 0;
        counter++;
        if (counter) {
            result = ADRES;
            LATD = result >> 6;
            counter = 0;
        }
    } else if (PIR2bits.CCP2IF) {
        PIR2bits.CCP2IF = 0;
    }
    
    return;
}

void main(void) {
    /* initial settings */
    OSCCONbits.IRCF = 0b110; // set oscillator to 4Mz => 0.25us
    
    INTCONbits.GIE = 1; // turn on global interrupt
    RCONbits.IPEN = 1;
    
    /* ADC settings */
    ADCON0bits.ADON = 1;
    
    // bit5 ~ 4: use VDD and VSS as refernce
    // bit3 ~ 0: set AD0 on only
    ADCON1 = 0b00001110;
    
    // bit7: right justified
    // bit5 ~ 3: TACQ = 2.4 / 0.7 ~= 3 => 4 TAD
    // bit 2 ~ 0: 4 TOSC => 0.7 / 0.25 ~= 2.8 => 4 TOSC
    ADCON2 = 0b10010100;
    
    /* A/D interrupt */
    PIE1bits.ADIE = 1; // enable A/D interrupt
    PIR1bits.ADIF = 0; // clear A/D interrupt flag
    IPR1bits.ADIP = 1; // set A/D interrupt to high prority
    
    /* I/O settings */
    TRISA = 1; // sets RA0 to input
    
    TRISD = 0; // setup RD0-RD4 to outputs
    LATD = 0; // turn off all LEDs at the beginning
    
    /* Enable CCP2 Interrupt  */ 
    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP =1;
    CCP2CONbits.CCP2M = 0b1011;
    //set comparator value, 1 sec = 4M / 4 / 8 = 125000, interrupt when TIMER3==CCPR2
    //so set CCPR2 = 25000, when it counts 125000 / 25000 = 5 times, it equals to 1 sec
    //1 sec passed we can acquire the ADRES value to result
    CCPR2 = 25000;

    /* Timer 3 configuration */
    
    //bit6, 3: Timer3 is the capture/compare clock source for CCP2;
    //bit 5 ~ 4:  1:8 Prescale value
    //bit1: Internal clock (FOSC/4)
    //bit0: //Set Timer3 On
    T3CON = 0b00111001;
    
    while (1) {
        /* waiting */
    }
    
    return;
}