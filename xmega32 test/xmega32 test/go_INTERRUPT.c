#include "include_file.h"

void interrupt_init(void)
{
	PMIC_CTRL&=~(1 << 7) | (1 << 6);
	PMIC_CTRL|= (1 << 0) | (1 << 1) | (1 << 2); // разрешение прерываний всех уровней
	sei(); //общее разрешение прерывания
}