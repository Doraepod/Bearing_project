#define F_CPU 32000000
#include <avr/io.h>
#include <util/delay.h>


void osc_init()
{
	OSC_CTRL |= OSC_RC32MEN_bm;					//Enable internal 32MHz oscillator
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));		//Wait till internal oscillator is ready to work
	CCP = CCP_IOREG_gc;							//Enable protected memory change (for 4 tacts)
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;			//Set 32MHz oscillator as clock source
	OSC_CTRL &= !OSC_RC2MEN_bm;					//Disable internal 2MHz oscillator
}

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
	USARTC0_DATA = data;						//send first half
	while(!(USARTC0_STATUS & USART_DREIF_bm));	//wait while buffer is empty
	USARTC0_DATA = data >> 8;					//send second half
}

void adc_init()
{
	ADCA_CTRLB = ADC_RESOLUTION_12BIT_gc;				//12 bit resolution (8bit, left adjusted 12 bit)
	ADCA_CH0_CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;	//Single ended mode with no gain
	ADCA_PRESCALER = ADC_PRESCALER_DIV32_gc;			//Prescaler x32 (x4/x8/x16/x32/x64/x128/x256/x512)
	ADCA_REFCTRL = ADC_REFSEL_AREFA_gc;					//Set ArefA as reference voltage
	ADCA_CH0_MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;			//Choose pin1 to convert source (initially PA1)
	ADCA_CTRLA = ADC_ENABLE_bm;							//Enable conversion
}

uint16_t adc_read(uint8_t port)
{
	ADCA_CTRLA |= ADC_FLUSH_bm;
	ADCA_CH0_MUXCTRL = port << 3;
	ADCA_CTRLA |= ADC_CH0START_bm;
	return ADCA_CH0RES;
}

int main(void)
{
	PORTC_DIR = 1 << 3;
	uint16_t value;
	PORTA_DIR &= 0 << 1;	//Set PA1 as input (just in case) 
	PORTB_DIR = 0b11111111; 
	PORTB_OUT = 0b11111111;
	osc_init();
	usart_init();
	adc_init();
    while (1) 
    {
		value = adc_read(1);
		PORTB_OUTTGL = 1 << 1;
		_delay_ms(10);
//		usart_send_string("hello world/r/n");
		usart_send_int(value);
    }
}