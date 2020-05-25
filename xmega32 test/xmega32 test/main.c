#include "include_file.h"
//uint16_t value; //значение выхода АЦП
 

void start(void)
{
	osc_init();	// настройка частоты 32МГц
	usart_init(); // включение USART
	//adc_init(); //Включение АЦП
	timer_init(); //включение таймера
	interrupt_init(); //включение прерывания
	//i2c_master_init(); //Включение i2c
	i2c_ADC();
}

int i = 0;
ISR(TCC0_OVF_vect)
{
	//value= adc_read(1); // считываем значение из АЦП
	Data_in();
	i++;
	if (i == 50) {	interrupt_close(); PORTD_OUT = 0xff;}
}


int main(void)
{
	PORTC_DIR = 0x00;
	PORTD_DIR = 0xff;
	//PORTD_OUT = 0xff;
	start(); //включение всего
	//PORTD_OUTCLR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП
	//PORTD_OUTTGL = 1;
	
	i2c_war();
	while (1)
	{
		//usart_send_string("hello word"); //вывод на USART  hello word		
		//usart_send_int(value); // вывод на USART значение с АЦП
		if(i >= 50)
		{
			//PORTD_OUTTGL = 0xff;
			Data_out();
			break;
		}
	_delay_ms(1);
	}
	while(1) {}
		
}