#include "interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
		uint8_t interruptnumber,
		uint16_t codeSegmentSelectorOffset,
		void (*handler)(),
		uint8_t DescriptorPrivilegeLevel,
		uint8_t DescriptorType)
{

	const uint8_t IDT_DESC_PRESENT = 0x80;

	interruptDescriptorTable[interruptnumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
	interruptDescriptorTable[interruptnumber].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
	interruptDescriptorTable[interruptnumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	interruptDescriptorTable[interruptnumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel&3) << 5);
	interruptDescriptorTable[interruptnumber].reserved = 0;

}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
{
	uint16_t CodeSegment = gdt->CodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xE;

	for(uint16_t i=0; i<256; i++)
		SetInterruptDescriptorTable[i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE];

	SetInterruptDescriptorTable[0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE];
	SetInterruptDescriptorTable[0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE];

	InterruptDescriptorTablePointer idt;
	idt.size = 256 * sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m" (idt));

}

InterruptManager::~InterruptManager()
{
}


void InterruptManager::Activate()
{
	asm("sti");
}


 uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp)
 {
 	printf(" INTERRUPT");

 	return esp;
 }
