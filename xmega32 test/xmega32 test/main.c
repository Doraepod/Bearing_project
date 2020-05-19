#include "include_file.h"
//uint16_t value; //значение выхода АЦП
 
void start(void)
{
	osc_init();	// настройка частоты 32МГц
	usart_init(); // включение USART
	//adc_init(); //Включение АЦП
	interrupt_init(); //включение прерывания
	//timer_init(); //включение таймера
	//i2c_master_init(); //Включение i2c
	i2c_ADC();
}

/*
ISR(TCC0_OVF_vect)
{
	value= adc_read(1); // считываем значение из АЦП
}
*/

int main(void)
{

	PORTC_DIR = 0x00;
	start(); //включение всего
	PORTD_DIR = 1;
	PORTD_OUTCLR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП
	//PORTD_OUTTGL = 1;
	i2c_war();
	while (1)
	{
		//usart_send_string("hello word"); //вывод на USART  hello word		
		//usart_send_int(value); // вывод на USART значение с АЦП
		Data_in();
		_delay_ms(5000);
		Data_out();
	}	
}