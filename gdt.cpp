#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024,0x9A),
dataSegmentSelector(0,64*1024*1024,0x92)
{

	uint32_t i[2];
	i[0] = (uint32_t)this;
	i[1] = sizeof(GlobalDescriptorTable) << 16;

	asm volatile("lgdt (%0)": :"p"(((uint8_t *) i)+2));

}

GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
	return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
	return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentSelector::SegmentSelector(uint32_t base, uint32_t limit, uint8_t flags)
{

	uint8_t* target = (uint8_t*)this;

	if(limit <= 65536)
	{
		target[6] = 0x40;
	}
	else
	{
		
	}


}