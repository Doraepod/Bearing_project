#include "include_file.h"
uint16_t value; //значение выхода АЦП

void start(void)
{
	osc_init();			//Настройка частоты 32МГц
	usart_init();		//Включение USART
	adc_init();			//Включение АЦП
	interrupt_init();	//включение прерывания
	timer_init();		//включение таймера
	i2c_master_init();	//Включение i2c
	lcd_init();			//Настройка LCD
}

ISR(TCC0_OVF_vect)
{
	value= adc_read(1); // считываем значение из АЦП
}

int main(void)
{
	PORTC_DIR = 0x00;
	start(); //включение всего
	PORTD_DIR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП
	while (1)
	{
		PORTD_OUTTGL = 1;
		_delay_ms(500);
		lcd_string(0, 0, "abc");
		//usart_send_string("hello word"); //вывод на USART  hello word		
		//usart_send_int(value); // вывод на USART значение с АЦП
	}
}