#include "include_file.h"

void osc_init()
{
	OSC_CTRL |= OSC_RC32MEN_bm;					//Enable internal 32MHz oscillator Включить внутренний генератор 32 МГц
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));		//Wait till internal oscillator is ready to work ожидание готовности к работе внутреннего генератора
	CCP = CCP_IOREG_gc;							//Enable protected memory change (for 4 tacts)
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;			//Set 32MHz oscillator as clock source включение 32МГц
	OSC_CTRL &= !OSC_RC2MEN_bm;					//Disable internal 2MHz oscillator отключение 2Мгц 
}