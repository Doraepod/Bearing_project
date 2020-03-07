#ifndef DEFINE_CHECK
	#define DEFINE_CHECK
	#define F_CPU 32000000 // ��� ��������� �������

	#include <avr/io.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <util/delay.h>
	#include <avr/interrupt.h>

	#include "go_UART.h" // UART 
	#include "go_ADC.h"  //  ��� 
 	#include "go_RIGHT_FREQUENCY.h" // ��������� ������� 32 ���
	#include "go_TIMER.h" // ������
	#include "go_INTERRUPT.h" // ���������� 
	#include "go_TWI.h" // TWI
#endif