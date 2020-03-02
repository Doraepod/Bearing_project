#include "include_file.h"

void start(void)
{
	osc_init(); // ��������� ������� 32���
	usart_init(); // ��������� USART
	adc_init(); //��������� ���
	interrupt_init(); //��������� ����������
	timer_init(); //��������� �������
}

ISR(TCC0_OVF_vect)
{
	PORTB_OUTTGL = 1;
}

int main(void)
{
	uint16_t value; //�������� ������ ���
	PORTB_DIR = 3;
	start(); //��������� �����
		
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) ��� �������� ���������� ���
	 
	while (1)
	{
		value = adc_read(1); // ������ ���
		_delay_ms(3000);
		 usart_send_string("hello word"); //����� �� USART  hello word
		usart_send_int(value); // ����� �� USART �������� � ���
	}
}