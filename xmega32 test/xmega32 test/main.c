#include "include_file.h"
//uint16_t value; //�������� ������ ���
 

void start(void)
{
	osc_init();	// ��������� ������� 32���
	usart_init(); // ��������� USART
	//adc_init(); //��������� ���
	timer_init(); //��������� �������
	interrupt_init(); //��������� ����������
	//i2c_master_init(); //��������� i2c
	i2c_ADC();
}

int i = 0;
ISR(TCC0_OVF_vect)
{
	//value= adc_read(1); // ��������� �������� �� ���
	Data_in();
	i++;
	if (i == 50) {	interrupt_close(); PORTD_OUT = 0xff;}
}


int main(void)
{
	PORTC_DIR = 0x00;
	PORTD_DIR = 0xff;
	//PORTD_OUT = 0xff;
	start(); //��������� �����
	//PORTD_OUTCLR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) ��� �������� ���������� ���
	//PORTD_OUTTGL = 1;
	
	i2c_war();
	while (1)
	{
		//usart_send_string("hello word"); //����� �� USART  hello word		
		//usart_send_int(value); // ����� �� USART �������� � ���
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