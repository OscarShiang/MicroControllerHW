#include <xc.h>

extern unsigned int divide(unsigned int a, unsigned int b);

void main(void) {
    volatile unsigned int res = divide(20, 5);
    volatile unsigned char quotient = res >> 8;
    volatile unsigned char remainer = res & 0x0f;
    while(1) {};
    return;
}
