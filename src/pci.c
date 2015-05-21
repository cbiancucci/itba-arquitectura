#include "../include/stdio.h"
#include "../include/kasm.h"
#include "../include/pci.h"

void getPci() {
	int bus, device, code;
	int mask=0xFFFFFFFF;
	unsigned short vendorID,deviceID;
	for(bus = 0; bus < 256; bus++) { 
		for(device = 0; device < 32; device++) { 
			mask=((bit31 | bit30 | ((bus<<16) & bit23) | ((device<<11) & bit15) | (bit10 & 0) | (bit7 & 0)));
			
			_outl(PCI_INDEX, mask);
			code=_inl(PCI_DATA);

			if(code != 0xFFFFFFFF && code != 0x00000000) {
				vendorID= (code & 0x0000FFFF);
				deviceID= (code & 0xFFFF0000)>>16;

					printPci(vendorID, deviceID);
			}
		}
	}
}

void printPci(unsigned short vendor, unsigned short device) {
	int i;
	
	for(i=0; i<PCI_DEVTABLE_LEN; i++) {
	
		if(PciDevTable[i].VenId == vendor && PciDevTable[i].DevId == device) {
			printf("%s,%s", PciDevTable[i].Chip, PciDevTable[i].ChipDesc);
			putchar('\n');
		}
	}		
}

void lspci() {
	getPci();
}
