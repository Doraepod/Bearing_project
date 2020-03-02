#include "include_file.h"

void i2c_master_init()
{
	TWIC_MASTER_BAUD = 155;								//Set i2c frequency. To calculate use equation BAUD = F_CPU / (2 * F_i2c) - 5
	TWIC_MASTER_CTRLA = TWI_MASTER_INTLVL_HI_gc			//Set i2c high level interrupt
	| TWI_MASTER_RIEN_bm			//Enable i2c read
	| TWI_MASTER_WIEN_bm			//Enable i2c write
	| TWI_MASTER_ENABLE_bm;			//Enable i2c master
	TWIC_MASTER_CTRLB = TWI_MASTER_TIMEOUT_DISABLED_gc;	//Disable timeout
}

//Send adress to all slaves with R/W bit
void i2c_send_adress(uint8_t adress, uint8_t RW)
{
	TWIC_MASTER_ADDR = (adress << 1) + RW;
}

void i2c_write(uint8_t adress, uint8_t *write_data, uint8_t size)
{
	i2c_send_adress(adress, 0);
	while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );
	
	uint8_t i = 0;
	
	for(i = 0; i < size; i++)
	{
		TWIC_MASTER_DATA = write_data [i];
		while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );
	}
}

void i2c_read(uint8_t adress, uint8_t *read_data, uint8_t size)
{
	i2c_send_adress(adress, 1);
	uint8_t i = 0;
	
	for(i = 0; i < size; i++)
	{
		while( !(TWIC_MASTER_STATUS&TWI_MASTER_RIF_bm) );
		read_data[i] = TWIC_MASTER_DATA;
	}
}