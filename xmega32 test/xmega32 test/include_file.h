#ifndef DEFINE_CHECK
	#define DEFINE_CHECK
	#define F_CPU 32000000 // для настройки частоты
	#define KOL 4          // количество измерений за одно прерывание МК. т.к 4 датчика 4 измерения
	#define DD 200		   // количество передаваемых по USART на МК значений координат. Число координат = DD/4

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
	//#include "go_TWI.h" // TWI
	#include "i2c.h" // программный i2c 
	#include "go_external_ADC.h" //внешний АЦП (связь по I2C)
#endif