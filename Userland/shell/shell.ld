OUTPUT_FORMAT("binary")
ENTRY(main)
SECTIONS
{
	.text 0x400000 :
	{
		*(.text*)
		. = ALIGN(0x2000);
		*(.rodata*)
	}
	.data ALIGN(0x2000) :
	{
		*(.data*)
	}
	.bss ALIGN(0x2000) :
	{
		bss = .;
		*(.bss*)
	}

	endOfBinary = .;
}