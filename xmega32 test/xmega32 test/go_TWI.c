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

void i2c_write(uint8_t adress, uint8_t *write_data, uint8_t size)
{
	uint8_t i = 0;
	i2c_send_adress(adress, 0);
	_delay_us(500);
	for(i = 0; i < size; i++)
	{
		TWIE_MASTER_DATA = write_data[i];
		_delay_us(500);
	}
	TWIE_MASTER_CTRLC = TWI_MASTER_CMD_STOP_gc;
}

uint8_t i2c_read(uint8_t adress)
{
	i2c_send_adress(adress, 1);
	_delay_us(1000);
	return TWIE_MASTER_DATA;
}

