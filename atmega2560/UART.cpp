/* 
 * File:   UART.cpp
 * Author: Levin Messing <levin@inode.at>
 * 
 * Created on 16. Oktober 2017, 15:50
 */

#include "UART.h"


UART::UART() {
  
  cli();
  
//  DDRE |= (1<<PE1);
//  DDRE &= ~(1<<PE0);
//  
  //baud = 57600
  UBRR0H = (uint8_t) (16>>8);
  UBRR0L = (uint8_t) (16 & 0x0ff);
  //set/clear flags and disable double speed mode and disable MPCM
  UCSR0A |= (1<<TXC0);
  UCSR0A &= ~((1<<FE0) | (1<<DOR0) | (1<<UPE0) | (1<<U2X0) | (1<<MPCM0));
  //disable interrupt
  UCSR0B &= ~((1<<RXCIE0) | (1<<TXCIE0) | (1<<UDRIE0));
  //enable receiver/transmitter
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  //8bit and 2 stop bits
  UCSR0B &= ~(1<<UCSZ02);
  UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
  //no parity, asynchronous
  UCSR0C &= ~((1<<UMSEL01) | (1<<UMSEL00) | (1<<UPM01) | (1<<UPM00) | (1<<USBS0) | (1<<UCPOL0));
 
  
  
  
  sei();
}

UART::UART(const UART& orig) {
}

UART::~UART() {
}

void UART::sendChar(const char data) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void UART::sendChar(const char data[]) {
  uint8_t i = 0;
  while (data[i] != '\0') {
    sendChar(data[i]);
    i++;
  }
}

char UART::getChar() {
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}