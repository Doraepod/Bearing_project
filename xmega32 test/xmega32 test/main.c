#include "include_file.h"

void start(void)
{
	osc_init();	// ��������� ������� 32���
	usart_init(); // ��������� USART
	//adc_init(); //��������� ���
	timer_init(); //��������� �������
	interrupt_init(); //��������� ����������
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
	//PORTD_DIR = 0xff;  ��� �����������
	//PORTD_OUTCLR = 1;
	
	start(); //��������� �����

	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) ��� �������� ���������� ���

	
	while (1)
	{
		//usart_send_string("hello word"); //����� �� USART  hello word		
		//usart_send_int(value); // ����� �� USART �������� � ���
		if(i >= 50)
		{
			Data_out();
			break;
		}
	_delay_ms(1);
	}
	while(1) {}
		
}