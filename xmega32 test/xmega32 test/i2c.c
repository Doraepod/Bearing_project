//=======================================================================
//					       Подключаемые файлы
//=======================================================================
#include "include_file.h"
#include "i2c.h"
uint16_t value1[KOL];
uint16_t value;
int R;
float otvet;
float temp;
int lastotvet;
int otvetxy[4];
int y;


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
	for (int you = 0; you < KOL-1; you++)
	{
		value1[you] = i2c_read_byte(ACK);
	}
	value1[KOL-1] = i2c_read_byte(NACK);
	i2c_stop();
}
/*обычный вывод по USART массива значегий -----
void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		usart_send_int(value1[you]);
		_delay_ms(100);
	}
}
*/
/* кривой вариант принять значения с АЦП -----
void Data_in(void)
{
	for (int you = 0; you < KOL; you++)
	{
		i2c_init();
		i2c_start();
		R = i2c_send_byte(0b10010001);//адрес ацп + команда на чтение
		value1[you] = i2c_read_byte(NACK);
		i2c_stop();
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

void Data_out(void)
{
	for (int you = 0; you < KOL; you++)
	{
		temp = (((float)value1[you]) / 255 ) * 10; // значение напряжения
		otvet = ( (temp - 0.11783) / 2.365 ) + 0.45;
		lastotvet = otvet * 1000;
		otvetxy[you] = lastotvet;
	}

		y=(otvetxy[0]-otvetxy[1])/2;
		y= 2000 + y;
		usart_send_int(y);
		_delay_ms(100);
		y=(otvetxy[2]-otvetxy[3])/2;
		y=  2000 + y;
		usart_send_int(y);
		_delay_ms(100);
	
}