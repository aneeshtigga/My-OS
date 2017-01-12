#ifndef __GDT_H
#define __GDT_H

#include "types.h"

	class GlobalDescriptorTable
	{

		public:
			class SegmentDescriptor
			{
			private:
				uint16_t limit_lo;
				uint16_t base_lo; //lo byte for the pointer
				uint8_t base_hi; //pointer extension 1 byte
				uint8_t type; //access bytes
				uint8_t flags_limit_hi;
				uint8_t base_vhi;
			public:
				SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
				uint32_t Base();
				uint32_t Limit();

			} __attribute__((packed));

		SegmentDescriptor nullSegmentSelector;
		SegmentDescriptor unusedSegmentSelector;
		SegmentDescriptor codeSegmentSelector;
		SegmentDescriptor dataSegmentSelector;	

	public:
		GlobalDescriptorTable(); //constructor
		~GlobalDescriptorTable(); //distructor

		uint16_t CodeSegmentSelector();
		uint16_t DataSegmentSelector();

	};