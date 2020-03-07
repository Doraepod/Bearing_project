#include "include_file.h"

void timer_init(void)
{
	TCC0_PER = 62500; //частота 2 секунда
	TCC0_CTRLE = TC_BYTEM_NORMAL_gc; // 16-битынй таймер
	TCC0_CTRLB = TC_WGMODE_NORMAL_gc; 	//нормальная работа таймера
	TCC0_INTCTRLA = TC0_OVFINTLVL_gm; // разрешение прерываний по переполнению
	TCC0_CTRLA = TC_CLKSEL_DIV1024_gc;// выход предделителя CLK/1024
}