#include "include_file.h"

void adc_init()
{
	ADCA_CTRLB = ADC_RESOLUTION_12BIT_gc;				//12 bit resolution (8bit, left adjusted 12 bit)  12-битный АЦП
	ADCA_CH0_CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;	//Single ended mode with no gain  режим без усилителя
	ADCA_PRESCALER = ADC_PRESCALER_DIV32_gc;			//Prescaler x32 (x4/x8/x16/x32/x64/x128/x256/x512) Предделитель 32
	ADCA_REFCTRL = ADC_REFSEL_AREFA_gc;					//Set ArefA as reference voltage опорное напряжение на PA0 
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;			//Choose pin1 to convert source (initially PA1) считываем значение с порта PA1
	ADCA_CTRLA = ADC_ENABLE_bm;							//Enable conversion  разрешение работы
}

uint16_t adc_read(uint8_t port)
{
	ADCA_CH0_MUXCTRL = port << 3;   //считываем значение с порта PA1
	ADCA_CTRLA |= ADC_CH0START_bm;  //запуск преобразователя
	return ADCA_CH0RES;				//вывод значение АЦП
}