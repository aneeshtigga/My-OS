#include "interrupts.h"

 void printf(char* str);

 uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp)
 {
 	printf(" INTERRUPT");

 	return esp;
 }