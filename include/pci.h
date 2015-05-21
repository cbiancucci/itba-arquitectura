#define bit31 0x80000000 
#define bit30 0x7F000000
#define bit23 0x00FF0000
#define bit15 0x0000F800
#define bit10 0x00000700
#define bit7 0x000000FF

#define PCI_INDEX 0xCF8
#define PCI_DATA 0xCFC

/* Fuente: http://www.waste.org/~winkles/hardware/pci.htm */

void getPci();
void printPci(unsigned short vendor, unsigned short device);

typedef struct _PCI_DEVTABLE
{
	unsigned short	VenId ;
	unsigned short	DevId ;
	char *	Chip ;
	char *	ChipDesc ;
}  PCI_DEVTABLE, *PPCI_DEVTABLE ;

PCI_DEVTABLE	PciDevTable [] =
{
	{0x8086, 0x3B00, "Intel(R) 5 Series/3400 Series Chipset ","LPC Interface Controller" } ,
	{0x8086, 0x2C52, "Intel Corporation ","Core Processor QuickPath Architecture Generic Non-Core Registers" } ,
	{0x8086, 0x2C81, "Intel Corporation","Core Processor QuickPath Architecture System Address Decode" } ,
	{0x11D4, 0x989B, "AD1989B", "SoundMax Integrated Digital HD Audio" },
	{0x80ee, 0xcafe, "VBoxVideo 0x8168", "VirtualBox Graphics Adapter" },
	{0x80ee, 0xbeef, "VBoxVideo 0x8168", "VirtualBox Guest Service" },
	{ 0x1025, 0x5237, "M5237", "Intel(R) 5 Series/3400 Series Chipset Family 4 Port SATA AHCI Controller - 3B29" } 
};

#define	PCI_DEVTABLE_LEN	(sizeof(PciDevTable)/sizeof(PCI_DEVTABLE))


