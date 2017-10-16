/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UART.h
 * Author: Levin Messing <levin@inode.at>
 *
 * Created on 16. Oktober 2017, 15:50
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/interrupt.h>

class UART {
public:
  UART();
  UART(const UART& orig);
  ~UART();
  
  void sendChar(const char data);
  void sendChar(const char data[]);
  char getChar();
private:

};

#endif /* UART_H */

