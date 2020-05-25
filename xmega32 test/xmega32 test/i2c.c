//=======================================================================
//					       Подключаемые файлы
//=======================================================================
#include "include_file.h"
#include "i2c.h"
 uint16_t value1[DD];
 uint16_t value;
 int R;
 float otvet;
 float temp;
 int lastotvet;
 int otvetxy[DD];
 int y;
 int non=0;
 

//=======================================================================
//					       Функция генерирующая условия стоп
//=======================================================================

BYTE i2c_stop(void)
	{
		BYTE error = 0;
		
		NULL_SCL();
		I2C_DELAY();
		NULL_SDA();
		I2C_DELAY();
		
		ONE_SCL();
		I2C_DELAY();
		ONE_SDA();
		I2C_DELAY();
		
		if((I2C_PIN & (1 << I2C_SDA)) == 0) error = 2;
		if((I2C_PIN & (1 << I2C_SCL)) == 0) error |= 1;
		I2C_DELAY();
		I2C_DELAY();
		I2C_DELAY();
		I2C_DELAY();
		
		return error;
	}
	
//=======================================================================
//					       Функция генерирующая условия старт
//=======================================================================

void i2c_start(void)
	{
		NULL_SDA();
		I2C_DELAY();
		NULL_SCL();
		I2C_DELAY();
	}
	
//=======================================================================
//					       Функция генерирующая условия рестарт
//=======================================================================

void i2c_restart(void)
	{
		ONE_SDA();
		I2C_DELAY();
		ONE_SCL();
		I2C_DELAY();
		
		NULL_SDA();
		I2C_DELAY();
		NULL_SCL();
		I2C_DELAY();
	}
	
//=======================================================================
//					       Функция инициализации шины
//=======================================================================

void i2c_init(void)
	{
		ONE_SDA();
		ONE_SCL();
		
		i2c_stop();
	}
	
//=======================================================================
//					       Функция отправки байта по шине
//=======================================================================

BYTE i2c_send_byte(BYTE data)
	{
		BYTE i;
		BYTE ask = ACK;
		
		for(i = 0; i < 8; i++)
			{
				if((data & 0x80) == 0)
					{
						NULL_SDA();
					}
				else
					{
						ONE_SDA();
					}
				I2C_DELAY();
				ONE_SCL();
				I2C_DELAY();
				NULL_SCL();
				
				data = (data << 1);
			}
			
		ONE_SDA();
		I2C_DELAY();
		ONE_SCL();
		I2C_DELAY();
		
		if((I2C_PIN & (1 << I2C_SDA)) == (1 << I2C_SDA))
			{
				ask = NACK;
			}
		else
			{
				ask = ACK;
			}
			
		NULL_SCL();
			
		return ask;
	}
	
//=======================================================================
//					       Функция чтения байта c шинs
//=======================================================================

BYTE i2c_read_byte(BYTE ask)
	{
		BYTE byte = 0;
		BYTE i;
		
		ONE_SDA();
		
		for(i = 0; i < 8; i++)
			{
				byte = (byte << 1);
				ONE_SCL();
				I2C_DELAY();
				if((I2C_PIN & (1 << I2C_SDA)) == (1 << I2C_SDA)) byte |= 0x01;
				NULL_SCL();
				I2C_DELAY();
			}
			
		if(ask == ACK)
			{
				NULL_SDA();
			}
		else
			{
				ONE_SDA();
			}
		I2C_DELAY();
		ONE_SCL();
		I2C_DELAY();
		NULL_SCL();
		I2C_DELAY();
		ONE_SDA();
			
		return byte;
	}

//=======================================================================
//					       инициализация ADC
//=======================================================================
	
void i2c_ADC(void)
{
	i2c_init();
	i2c_start();
	R = i2c_send_byte(0b10010000);//адрес ацп + команда на запись
	R = i2c_send_byte(0b01000100);//команда для ацп
	i2c_stop();
	
}

void i2c_war(void)
{
		i2c_init();
		i2c_start();
		R = i2c_send_byte(0b10010001);//адрес ацп + команда на чтение
		value = i2c_read_byte(NACK);
		i2c_stop();
}
void Data_in(void)
{
	i2c_init();
	i2c_start();
	R = i2c_send_byte(0b10010001);//адрес ацп + команда на чтение
	int you;
	for (you = 0; you < KOL-1; you++)
	{
		value1[non] = i2c_read_byte(ACK);
		non++;
	}
	value1[non] = i2c_read_byte(NACK);
	non++;
	i2c_stop();
}

/*
void Data_in(void)
{
	i2c_init();
	i2c_start();
	R = i2c_send_byte(0b10010001);//адрес ацп + команда на чтение
	for (int you = 0; you < KOL-1; you++)
	{
		value1[you] = i2c_read_byte(ACK);
	}
	value1[KOL-1] = i2c_read_byte(NACK);
	i2c_stop();
}*/
/*обычный вывод по USART массива значегий -----
void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		usart_send_int(value1[you]);
	}
}*/

/* нормальный вариант вывода по USART всех посчитанных значений расстояиня +++
void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		temp = (((float)value1[you]) / 255 ) * 10; // значение напряжения 
		otvet = ( (temp - 0.11783) / 2.365 ) + 0.45;
		lastotvet = otvet * 1000;
		usart_send_int(lastotvet);
		_delay_ms(100);
	}
}*/
/* последняя версия
void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		temp = (((float)value1[you]) / 255 ) * 10; // значение напряжения
		otvet = ( (temp - 0.11783) / 2.365 ) + 0.45;
		lastotvet = otvet * 1000;
		usart_send_int(lastotvet);
		otvetxy[you] = lastotvet;
		_delay_ms(50);
	}

		y=(otvetxy[0]-otvetxy[1])/2;
		y= 2000 + y;
		usart_send_int(y);
		_delay_ms(50);
		y=(otvetxy[2]-otvetxy[3])/2;
		y=  2000 + y;
		usart_send_int(y);
		_delay_ms(50);
	
}*/
/*
void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		temp = (((float)value1[you]) / 255 ) * 10; // значение напряжения
		otvet = ( (temp - 0.11783) / 2.365 ) + 0.45;
		lastotvet = otvet * 1000;
		otvetxy[you] = lastotvet;
	}
	
	for (int you = 0; you < KOL; you++)
	{
		usart_send_int(otvetxy[you]);
		_delay_ms(10);
	}
	usart_send_string("hello word");
	
	for (int you = 0; you < KOL; you+=4)
	{
		y=(otvetxy[you]-otvetxy[you+1])/2;
		y= 2000 + y;
		usart_send_int(y);
		_delay_ms(10);
		y=(otvetxy[you+2]-otvetxy[you+3])/2;
		y=  2000 + y;
		usart_send_int(y);
		_delay_ms(10);
	}
	usart_send_string("hello word");	
}*/
void Data_out(void)
{
	int you;
	for (you = 0; you < DD; you++)
	{
		temp = (((float)value1[you]) / 255 ) * 10; // значение напряжения
		otvet = ( (temp - 0.11783) / 2.365 ) + 0.45;
		lastotvet = otvet * 1000;
		otvetxy[you] = lastotvet;
	}
	for (you = 0; you < DD; you++)
	{
		int pop = otvetxy[you];
		usart_send_int(pop);
	}
	for (you = 0; you < DD; you+=4)
	{
		y=(otvetxy[you]-otvetxy[you+1])/2;
		y= 2000 + y;
		usart_send_int(y);
		y=(otvetxy[you+2]-otvetxy[you+3])/2;
		y=  2000 + y;
		usart_send_int(y);
	}
}