void printf(char* str)
{
	unsigned short* VideoMemory = (unsigned short*)0xb8000;
	for(int i=0; str[i] != '\0'; ++i)
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

extern "c" constructor start_ctors;
extern "c" constructor end_ctors;

extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
	printf("Hello Aneesh! --- http://www.google.com");

	while(1);

}