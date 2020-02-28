#include "main_include_file.h"

void osc_init()
{
	OSC_CTRL |= OSC_RC32MEN_bm;					//Enable internal 32MHz oscillator
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));		//Wait till internal oscillator is ready to work
	CCP = CCP_IOREG_gc;							//Enable protected memory change (for 4 tacts)
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;			//Set 32MHz oscillator as clock source
	OSC_CTRL &= !OSC_RC2MEN_bm;					//Disable internal 2MHz oscillator
}