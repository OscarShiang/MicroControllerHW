#include <xc.h>

extern unsigned int devide(unsigned int a, unsigned int b);

void main(void) {
    volatile unsigned int res = devide(17, 5);
    volatile unsigned char quotient = res >> 8;
    volatile unsigned char remainer = res;
    while(1) {};
    return;
}
