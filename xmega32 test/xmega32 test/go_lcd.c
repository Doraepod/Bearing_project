#include "include_file.h"

void lcd_command(uint8_t command)
{
	uint8_t command_send[4];
	command_send[0] = (command & 0xF0) + 0b00001100;
	command_send[1] = (command & 0xF0) + 0b00001000;
	command_send[2] = ((command & 0x0F) << 4) + 0b00001100;
	command_send[3] = ((command & 0x0F) << 4) + 0b00001000;
	i2c_write(lcd_addr, *command_send, 4);
}

void lcd_symbol(uint8_t symbol)
{
	uint8_t symbol_send[4];
	symbol_send[0] = (symbol & 0xF0) + 0b00001101;
	symbol_send[1] = (symbol & 0xF0) + 0b00001001;
	symbol_send[2] = ((symbol & 0x0F) << 4) + 0b00001101;
	symbol_send[3] = ((symbol & 0x0F) << 4) + 0b00001001;
	i2c_write(lcd_addr, *symbol_send, 4);
}

void lcd_position(uint8_t line, uint8_t position)
{
	uint8_t start_position;
	if(line)
		start_position = 0x40;
	else
		start_position = 0x00;
	start_position = start_position + position;
	lcd_command(lcd_addr, 0x80 | start_position);
}

void lcd_string(uint8_t line, uint8_t position, uint8_t *data)
{
	lcd_position(line, position);
	while(*data)	
	{
		lcd_symbol(*data);
		data++;
	}
}

void lcd_init()
{
	TWIE_MASTER_ADDR = 0b01001110;
	_delay_us(1000);
	
	TWIE_MASTER_DATA = 0b00000100;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b00000000;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b11000100;
	_delay_us(1000);
	TWIE_MASTER_DATA = 0b11000000;
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