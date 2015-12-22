/*
 * Timer.h
 *
 *  Created on: Dec 22, 2015
 *      Author: werner
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned long long micro_t;

class Timer {
public:
	Timer(unsigned long _freq);
	virtual ~Timer();
	void start(); // inicia contagem
	void reset(); // zera contagem
	void stop(); // para contagem
	void restart() {
		stop();
		reset();
		start();
	}
	micro_t microseconds();
	void isr_handler();
	static Timer * instance() { return timer; }
private:
	static Timer * timer;
	unsigned long long freq;
	volatile micro_t ticks;
};

#endif /* TIMER_H_ */
