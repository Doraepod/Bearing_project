#include "include_file.h"

void timer_init(void)
{
	TCC0_PER = 31250; //������� 1 �������
	TCC0_CTRLE = TC_BYTEM_NORMAL_gc; // 16-������ ������
	TCC0_CTRLB = TC_WGMODE_NORMAL_gc; 	//���������� ������ �������
	TCC0_INTCTRLA = TC0_OVFINTLVL_gm; // ���������� ���������� �� ������������
	TCC0_CTRLA = TC_CLKSEL_DIV256_gc;// ����� ������������ CLK/1024
}
