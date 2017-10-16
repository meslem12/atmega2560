/* 
 * File:   UART.cpp
 * Author: Levin Messing <levin@inode.at>
 * 
 * Created on 16. Oktober 2017, 15:50
 */

#include "UART.h"

UART::UART() {
  UBRR0 = 0b000000000000;
}

UART::UART(const UART& orig) {
}

UART::~UART() {
}

void UART::sendChar(const char data)
{
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

void UART::sendChar(const char data[])
{
  uint8_t i = 0;
  while(data[i] != '\0')
  {
    sendChar(data[i]);
    i++;
  }
}

char UART::getChar()
{
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}