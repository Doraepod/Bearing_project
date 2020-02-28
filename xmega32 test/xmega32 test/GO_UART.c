#include "main_include_file.h"

void usart_init()
{
	USARTC0_CTRLC = USART_CHSIZE0_bm | USART_CHSIZE1_bm;	//Set 8-bit data size
	
	//for non-negative values of scale BAUDRATE = Fosc / (2 ^ SCALE * 16 * (BSEL + 1)) or BSEL = Fosc / (2 ^ SCALE * 16 * BAUDRATE) - 1
	//for negative values of scale BAUDRATE = Fosc / 16 * (2 ^ SCALE * BSEL + 1) or BSEL = (Fosc / (16 * BAUDRATE) - 1) / 2 ^ SCALE
	USARTC0_BAUDCTRLA = 217;			//Lower 8 bits of rate set register (for 9600 rate BSEL should be 217 @32MHz)
	USARTC0_BAUDCTRLB = 0;				//Scale from -7 to 7 (0b1001 for -7)
	
	
	USARTC0_CTRLB |= USART_TXEN_bm;		//Enable usart transmit
}

void usart_send_char(char symbol)
{
	while(!(USARTC0_STATUS & USART_DREIF_bm));	//wait while buffer is empty
	USARTC0_DATA = symbol;							//send char
}

void usart_send_string(char *text)
{
	while(*text)
	{
		usart_send_char(*text++);
	}
}

void usart_send_int(uint16_t data)
{
	while(!(USARTC0_STATUS & USART_DREIF_bm));	//wait while buffer is empty
	USARTC0_DATA = data >> 8;						//send first half
	while(!(USARTC0_STATUS & USART_DREIF_bm));	//wait while buffer is empty
	USARTC0_DATA = data;					//send second half
}