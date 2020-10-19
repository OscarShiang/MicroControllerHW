#include <xc.inc>

; When assembly code is placed in a psect, it can be manipulated as a
; whole by the linker and placed in memory.  
;
; In this example, barfunc is the program section (psect) name, 'local' means
; that the section will not be combined with other sections even if they have
; the same name.  class=CODE means the barfunc must go in the CODE container.
; PIC18's should have a delta (addressible unit size) of 1 (default) since they
; are byte addressible.  PIC10/12/16's have a delta of 2 since they are word
; addressible.  PIC18's should have a reloc (alignment) flag of 2 for any
; psect which contains executable code.  PIC10/12/16's can use the default
; reloc value of 1.  Use one of the psects below for the device you use:

;psect   barfunc,local,class=CODE,delta=2 ; PIC10/12/16
psect   barfunc,local,class=CODE,reloc=2 ; PIC18

global _devide ; extern of bar function goes in the C source file
_devide:
	movff 0x001, TRISB
	movff 0x003, WREG
	clrf TRISA
    loop:
	cpfsgt TRISB
	goto devide_end
	subwf TRISB, F
	incf TRISA
	goto loop
    devide_end:
	movff TRISB, WREG
	movwf 0x001, F
	movff TRISA, WREG
	movwf 0x002, F
	return
