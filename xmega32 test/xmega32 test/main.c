#include "include_file.h"
uint16_t value; //значение выхода АЦП

void start(void)
{
	osc_init();	// настройка частоты 32МГц
	//usart_init(); // включение USART
	adc_init(); //Включение АЦП
	interrupt_init(); //включение прерывания
	timer_init(); //включение таймера
	i2c_master_init(); //Включение i2c
}


ISR(TCC0_OVF_vect)
{
	value= adc_read(1); // считываем значение из АЦП
}

int main(void)
{
	
	//PORTCFG.MPCMASK = 0x03; // Configure several PINxCTRL registers at the same time
	//PORTE.PIN0CTRL = (PORTE.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc; //Enable pull-up to get a defined level on the switches
	PORTC_DIR = 0x00;
	start(); //включение всего
	PORTD_DIR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) для опорного напрядения АЦП
	//lcd_init();
	//lcd_write();
	while (1)
	{
		lcd_init();//
		//i2c_send_adress(0b1111111, 0);
		PORTD_OUTTGL = 1;
		_delay_ms(500);
		//usart_send_string("hello word"); //вывод на USART  hello word		
		//usart_send_int(value); // вывод на USART значение с АЦП
	}
}