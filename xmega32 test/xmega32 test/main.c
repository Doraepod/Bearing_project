#include "include_file.h"
uint16_t value; //�������� ������ ���
	int R,W;
void start(void)
{
	osc_init();	// ��������� ������� 32���
	//usart_init(); // ��������� USART
	adc_init(); //��������� ���
	interrupt_init(); //��������� ����������
	timer_init(); //��������� �������
	//i2c_master_init(); //��������� i2c
}


ISR(TCC0_OVF_vect)
{
	value= adc_read(1); // ��������� �������� �� ���
}

int main(void)
{
	
	//PORTCFG.MPCMASK = 0x03; // Configure several PINxCTRL registers at the same time
	//PORTE.PIN0CTRL = (PORTE.PIN0CTRL & ~PORT_OPC_gm) | PORT_OPC_PULLUP_gc; //Enable pull-up to get a defined level on the switches
	PORTC_DIR = 0x00;
	start(); //��������� �����
	PORTD_DIR = 1;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) ��� �������� ���������� ���
	//lcd_init();
	//lcd_write();
		i2c_init();
		i2c_start();
		R = i2c_send_byte(0x4E);//
		
		R = i2c_send_byte(0b00101100); //�������� �����
		R = i2c_send_byte(0b00101000); 
		R = i2c_send_byte(0b10001100);
		R = i2c_send_byte(0b10001000);
		
		R = i2c_send_byte(0b10001100);
		R = i2c_send_byte(0b10001000);	//��������� ������� � ������ ���������
		R = i2c_send_byte(0b00001100);
		R = i2c_send_byte(0b00001000);

		R = i2c_send_byte(0b00111101);//
		R = i2c_send_byte(0b00111001);// ������� 3-���
		R = i2c_send_byte(0b00111101);//
		R = i2c_send_byte(0b00111001);//
			
	while (1)
	{
		//lcd_init();//
		//i2c_send_adress(0b1111111, 0);
		//PORTD_OUTTGL = 1;
		
	//i2c_restart(void);

	

//	v = i2c_stop();
	//i2c_read_byte(BYTE ask);	
		
		_delay_ms(500);
		//usart_send_string("hello word"); //����� �� USART  hello word		
		//usart_send_int(value); // ����� �� USART �������� � ���
	}	
}