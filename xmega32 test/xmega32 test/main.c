#include "include_file.h"

void start(void)
{
	osc_init(); // настройка частоты 32МГц
	usart_init(); // включение USART
	adc_init(); //Включение АЦП
	interrupt_init(); //включение прерывания
	timer_init(); //включение таймера
}

ISR(TCC0_OVF_vect)
{
	PORTB_OUTTGL = 1;
}

int main(void)
{
	uint16_t value; //значение выхода АЦП
	PORTB_DIR = 3;
	start(); //включение всего
		
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП
	 
	while (1)
	{
		value = adc_read(1); // чтение АЦП
		_delay_ms(3000);
		 usart_send_string("hello word"); //вывод на USART  hello word
		usart_send_int(value); // вывод на USART значение с АЦП
	}
}