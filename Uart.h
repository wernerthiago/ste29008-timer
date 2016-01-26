/*
 * Uart.h
 *
 *  Created on: 13 de nov de 2015
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_

#include "Circular_FIFO.h"
#include "avr/io.h"

class Uart {
private:
    static Uart uart;
	static const int Buffer_Size = 23;

public:
	Uart();
	bool has_data();
	void put(uint64_t c);
	uint64_t get();

	static void rx_interrupt_handler();
	static void empty_interrupt_handler();
	static void interruptoff();
	static void interrupton();

	Circular_FIFO<uint64_t,Buffer_Size> tx;
	Circular_FIFO<uint64_t,Buffer_Size> rx;
};

#endif /* UART_H_ */
