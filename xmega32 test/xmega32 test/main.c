#include "include_file.h"
uint16_t value; //�������� ������ ���

void start(void)
{
	osc_init();			//��������� ������� 32���
	usart_init();		//��������� USART
	adc_init();			//��������� ���
	interrupt_init();	//��������� ����������
	timer_init();		//��������� �������
	i2c_master_init();	//��������� i2c
	lcd_init();			//��������� LCD
}

ISR(TCC0_OVF_vect)
{
	value= adc_read(1); // ��������� �������� �� ���
}

int main(void)
{
	PORTC_DIR = 0x00;
	start(); //��������� �����
	PORTD_DIR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) ��� �������� ���������� ���
	while (1)
	{
		PORTD_OUTTGL = 1;
		_delay_ms(500);
		lcd_string(0, 0, "abc");
		//usart_send_string("hello word"); //����� �� USART  hello word		
		//usart_send_int(value); // ����� �� USART �������� � ���
	}
}