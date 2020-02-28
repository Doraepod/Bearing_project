#include "main_include_file.h"

int main(void)
{
	PORTC_DIR = 1 << 3;
	uint16_t value;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case)
	osc_init();
	usart_init();
	adc_init();
	while (1)
	{
		value = adc_read(1);
		_delay_ms(3000);
		//	usart_send_string("hello word");
		usart_send_int(value);
	}
}