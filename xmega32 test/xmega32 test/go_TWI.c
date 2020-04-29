#include "include_file.h"

void i2c_master_init()
{
	TWIE_MASTER_BAUD = 155;								//Set i2c frequency. To calculate use equation BAUD = F_CPU / (2 * F_i2c) - 5
	TWIE_MASTER_CTRLA = TWI_MASTER_INTLVL_HI_gc			//Set i2c high level interrupt
	| TWI_MASTER_RIEN_bm			//Enable i2c read
	| TWI_MASTER_WIEN_bm			//Enable i2c write
	| TWI_MASTER_ENABLE_bm;			//Enable i2c master
	TWIE_MASTER_CTRLB = TWI_MASTER_TIMEOUT_DISABLED_gc;	//Disable timeout
	TWIE_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

//Send adress to all slaves with R/W bit
void i2c_send_adress(uint8_t adress, uint8_t RW)
{
	TWIE_MASTER_ADDR = (adress << 1) + RW;
}

void i2c_write(uint8_t adress, uint8_t write_data)
{
	i2c_send_adress(adress, 0);
	while( !(TWIE_MASTER_STATUS & TWI_MASTER_WIF_bm) );
	TWIE_MASTER_DATA = write_data;
	while( !(TWIE_MASTER_STATUS & TWI_MASTER_WIF_bm) );
}

uint8_t i2c_read(uint8_t adress)
{
	i2c_send_adress(adress, 1);
	while( !(TWIE_MASTER_STATUS&TWI_MASTER_RIF_bm) );
	return TWIE_MASTER_DATA;
}

void lcd_init()
{
	TWIE_MASTER_ADDR = 0b01001110;
	_delay_us(1000);
	
	TWIE_MASTER_DATA = 0b00000100;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b00000000;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b10010100;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b10010000;
	_delay_us(1000);

		TWIE_MASTER_DATA = 0b00110101;
		_delay_us(1000);
		TWIE_MASTER_DATA = 0b00110001;
		_delay_us(1000);
		TWIE_MASTER_DATA = 0b00110101;
		_delay_us(1000);
		TWIE_MASTER_DATA = 0b00111001;
		_delay_us(1000);
}

void lcd_write()
{
	TWIE_MASTER_CTRLC = TWI_MASTER_CMD_REPSTART_gc;
	i2c_send_adress(0b00111111, 0);
	_delay_us(500);
	TWIE_MASTER_DATA = 0b00110101;
	_delay_us(500);
	TWIE_MASTER_DATA = 0b00110001;
	_delay_us(500);
	TWIE_MASTER_DATA = 0b00110101;
	_delay_us(500);
	TWIE_MASTER_DATA = 0b00110001;
	_delay_us(500);
}