#include "include_file.h"

void osc_init()
{
	OSC_CTRL |= OSC_RC32MEN_bm;					//Enable internal 32MHz oscillator �������� ���������� ��������� 32 ���
	while(!(OSC_STATUS & OSC_RC32MRDY_bm));		//Wait till internal oscillator is ready to work �������� ���������� � ������ ����������� ����������
	CCP = CCP_IOREG_gc;							//Enable protected memory change (for 4 tacts)
	CLK_CTRL = CLK_SCLKSEL_RC32M_gc;			//Set 32MHz oscillator as clock source ��������� 32���
	OSC_CTRL &= !OSC_RC2MEN_bm;					//Disable internal 2MHz oscillator ���������� 2��� 
}