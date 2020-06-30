#include "include_file.h"

void start(void)
{
	osc_init();	// настройка частоты 32МГц
	usart_init(); // включение USART
	//adc_init(); //Включение АЦП
	timer_init(); //включение таймера
	interrupt_init(); //включение прерывания
	external_ADC_init();
	external_ADC_war();
}

int i = 0;
ISR(TCC0_OVF_vect)
{
	Data_in();
	i++;
	if (i == 50) {	interrupt_close(); PORTD_OUT = 0xff;}
}


int main(void)
{
	PORTC_DIR = 0x00;
	//PORTD_DIR = 0xff;  для светодиодов
	//PORTD_OUTCLR = 1;
	
	start(); //включение всего

	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП

	
	while (1)
	{
		//usart_send_string("hello word"); //вывод на USART  hello word		
		//usart_send_int(value); // вывод на USART значение с АЦП
		if(i >= 50)
		{
			Data_out();
			break;
		}
	_delay_ms(1);
	}
	while(1) {}
		
}