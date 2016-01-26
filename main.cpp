/*
 * main.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: werner
 */
#include "Timer.h"
#include "Uart.h"
#include "util/delay.h"
#include "avr/interrupt.h"

int main(){
	Timer timer(128);
	Uart u;
	PINB = 0x23;
	DDRB = 0x24;
	PORTB = 0x80;
	sei();

	while(1){
		timer.start();
		_delay_us(10);
		timer.stop();
		micro_t tempo = timer.microseconds();
		u.put(tempo);
	}
	return 0;
}


