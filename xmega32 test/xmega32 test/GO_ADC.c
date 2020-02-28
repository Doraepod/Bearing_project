#include "main_include_file.h"

void adc_init()
{
	ADCA_CTRLB = ADC_RESOLUTION_12BIT_gc;				//12 bit resolution (8bit, left adjusted 12 bit)
	ADCA_CH0_CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;	//Single ended mode with no gain
	ADCA_PRESCALER = ADC_PRESCALER_DIV32_gc;			//Prescaler x32 (x4/x8/x16/x32/x64/x128/x256/x512)
	ADCA_REFCTRL = ADC_REFSEL_AREFA_gc;					//Set ArefA as reference voltage
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;			//Choose pin1 to convert source (initially PA1)
	ADCA_CTRLA = ADC_ENABLE_bm;							//Enable conversion
}

uint16_t adc_read(uint8_t port)
{
	ADCA_CH0_MUXCTRL = port << 3;
	ADCA_CTRLA |= ADC_CH0START_bm;
	return ADCA_CH0RES;
}