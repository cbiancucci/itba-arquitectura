#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <syscalls.h>
#include <video.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;
static uint64_t pitTimer = 0;
uint64_t screensaverWaitTime = 20;
uint64_t screensaverTimer = 0;
bool screensaverActive = FALSE;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	
	video_init();
	video_println("================================================================================");
	video_println("                                - SARASA SARASA -                               ");
	video_println("================================================================================");
	video_println("");
	video_println("");
	
	((EntryPoint)sampleCodeModuleAddress)();
	return 0;
}

void irq0_handler() {

	pitTimer++;
	screensaverTimer--;

	if (screensaverTimer == 0 && !screensaverActive) {
	//	activeScreensaver();
	}

}

bool screensaverResetTimer() {
	bool ret = FALSE;
	if (screensaverActive) {
		ret = TRUE;
		screensaverActive = FALSE;
		//video_trigger_restore();
	}
	screensaverTimer = 18 * screensaverWaitTime;
	return ret;
}

void activeScreensaver() {
	screensaverActive = TRUE;
	//video_trigger_screensaver();
}
