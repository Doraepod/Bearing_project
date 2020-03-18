#include "include_file.h"

void lcd_command(uint8_t command)
{
	uint8_t command_send[4];
	command_send[0] = (command & 0xF0) + 0b00001100;
	command_send[1] = (command & 0xF0) + 0b00001000;
	command_send[2] = ((command & 0x0F) << 4) + 0b00001100;
	command_send[3] = ((command & 0x0F) << 4) + 0b00001000;
	i2c_write(lcd_addr, command_send, 4);
}

void lcd_symbol(uint8_t symbol)
{
	uint8_t symbol_send[4];
	symbol_send[0] = (symbol & 0xF0) + 0b00001101;
	symbol_send[1] = (symbol & 0xF0) + 0b00001001;
	symbol_send[2] = ((symbol & 0x0F) << 4) + 0b00001101;
	symbol_send[3] = ((symbol & 0x0F) << 4) + 0b00001001;
	i2c_write(lcd_addr, symbol_send, 4);
}

void lcd_position(uint8_t line, uint8_t position)
{
	uint8_t start_position;
	if(line)
		start_position = 0x40;
	else
		start_position = 0x00;
	start_position = start_position + position;
	lcd_command(0x80 | start_position);
}

void lcd_string(uint8_t line, uint8_t position, char *data)
{
	lcd_position(line, position);
	while(*data)	
	{
		lcd_symbol(*data);
		data++;
	}
}

void lcd_int(uint8_t line, uint8_t position, int32_t number)
{
	char string[16];
	itoa(number, string, 10);
	lcd_string(line, position, string);
}

void lcd_init()
{
	lcd_command(0x28);	//2 lines, symbol size 5*8
	lcd_command(0x01);	//Clear
	lcd_command(0x06);	//Auto move cursor after each symbol
	lcd_command(0x0C);	//Light on, cursor off
	lcd_command(0x02);	//Initial position
	lcd_command(0x01);	//Clear
}