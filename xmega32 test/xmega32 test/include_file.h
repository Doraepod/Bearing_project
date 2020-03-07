#ifndef DEFINE_CHECK
	#define DEFINE_CHECK
	#define F_CPU 32000000 // для настройки частоты

	#include <avr/io.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>

	#include "go_UART.h" // UART 
	#include "go_ADC.h"  //  АЦП 
 	#include "go_RIGHT_FREQUENCY.h" // настройка частоты 32 МГц
	#include "go_TIMER.h" // таймер
	#include "go_INTERRUPT.h" // прерывания 
	#include "go_TWI.h" // TWI
#endif