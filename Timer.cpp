/*
 * Timer.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: werner
 */

#include "Timer.h"
#include "avr/interrupt.h"
#define Processor 16000000
#define Micro 0.000001
Timer * Timer::timer;

Timer::Timer(unsigned long _freq) {
	// TODO Auto-generated constructor stub
	this->freq = freq;
	if(freq > 62500){
		long int aux = Processor/_freq;
	}else{
		if((freq < 62500) && (freq > 62500/8)){
			long int aux = (Processor/8)/_freq;
		}else{
			//if((freq < 62500) && (freq > 62500/8))
		}
	}


	timer = this;
	TIMSK0 = 0x01;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

ISR(TIMER0_OVF_vect){
	isr_handler();
}

void Timer::isr_handler(){
	timer->ticks++;
}

void Timer::stop(){
	TCCR0B = 0x00;
}

void Timer::start(){
	TCCR0B = 0x01;
}

void Timer::reset(){
	TCNT0 = 0x00;
}

micro_t Timer::microseconds(){
	return ticks*;
}
