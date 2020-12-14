#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;

char str[20];
int enable_log = 0;

void main(void) 
{
    
    SYSTEM_Initialize() ;
    
    while(1) {
        if (enable_log) {
            float value = (float)ADC_Read(0x1) * 5 / 1024;
            sprintf(str, "%.2f\r\n", value);
            UART_Write_Text(str);
        }
    }
    return;
    
}

// old version: 
// void interrupt high_priority Hi_ISR(void)
void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.CCP1IF == 1) {
        RC2 ^= 1;
        PIR1bits.CCP1IF = 0;
        TMR3 = 0;
    }
    return ;
}