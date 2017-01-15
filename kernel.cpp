#include "types.h"
#include "gdt.h"

void printf(char* str)
{
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;
	//made a cursor to move around the display
	static uint8_t x=0, y=0;
	//display pane is 80 characters wide and 25 characters long
	for(int i=0; str[i] != '\0'; ++i)
	{	
		switch(str[i])
		{
			case '\n':
				y++;
				x=0;
				break;
			default:
				VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
				x++;
				break;
		}
		//if gets to the right end, the cursor moves to the next line
		if(x >= 80)
		{
			y++;
			x=0;
		}
		//if the cursor reaches bottom of the display, it'll start again from the top left.
		if(y >= 25)
		{
			for(y=0; y<25;y++)
				for(x=0;x<80;x++)
					VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

			x=0;
			y=0;
		}
	}

}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t /*magicnumber*/)
{
	printf("Hello Aneesh! --- http://www.google.com");

	GlobalDescriptorTable gdt;

	while(1);

}
