/*
 * Uart.cpp
 *
 *  Created on: 13 de nov de 2015
 *      Author: aluno
 */

#include "Uart.h"
#include "Circular_FIFO.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#define F_CPU 16000000UL
#define BAUD 9600
#include "util/setbaud.h"
Uart Uart::uart;

Uart::Uart(){
	//SERIAL
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = 0x06;
	UCSR0B = 0x98;
	//LED
	//PINB = 0x23;
	//DDRB = 0x24;
	//PORTB = 0x80;
}

void Uart::put(uint64_t c) {
    uart.tx.push(c);
    UCSR0B |= 0x20;
}

uint64_t Uart::get() {
    return uart.rx.pop();
}

bool Uart::has_data() {
    return uart.rx.has_data();
}

void Uart::rx_interrupt_handler() {
    uart.rx.push(UDR0);
}

void Uart::empty_interrupt_handler(){
    if(uart.tx.has_data())
        UDR0 = uart.tx.pop();
    else UCSR0B &= ~0x20;
}

ISR(USART_RX_vect ){
	Uart::rx_interrupt_handler();
}

ISR(USART_UDRE_vect ){
	Uart::empty_interrupt_handler();
}

void Uart::interrupton(){
	sei();
}

void Uart::interruptoff(){
	cli();
}
