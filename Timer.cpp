/*
 * Timer.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: werner
 */

#include "Timer.h"
#include "stdlib.h"
#include "avr/interrupt.h"
#define Processor 16000000
#define Micro 0.000001
Timer * Timer::timer;

void operator delete(void * p) {
	free(p);
}

Timer::Timer(unsigned long _freq) {
	// TODO Auto-generated constructor stub
	this->freq = freq;
	if(freq > 62500){
		this->aux = Processor/_freq;
	}else{
		if((freq < 62500) && (freq > 62500/8)){
			this->aux = (Processor/8)/_freq;
		}else{
			if((freq < 62500/8) && (freq > 62500/32)){
				this->aux = (Processor/32)/_freq;
			}else{
				if((freq < 62500/32) && (freq > 62500/64)){
					this->aux = (Processor/64)/_freq;
				}else{
					if((freq < 62500/64) && (freq > 62500/128)){
						this->aux = (Processor/128)/_freq;
					}else{
						if((freq < 62500/128) && (freq > 62500/256)){
							this->aux = (Processor/256)/_freq;
						}
					}
				}
			}
		}
	}
	timer = this;
	TIMSK0 = 0x01;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

ISR(TIMER0_OVF_vect){
	Timer::instance()->isr_handler();
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
	return ticks*this->aux;
}
