/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Port.h
 * Author: Levin Messing <levin@inode.at>
 *
 * Created on 16. Oktober 2017, 18:46
 */

#ifndef PORT_H
#define PORT_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

class Port {
public:
  Port(const uint8_t Pxn, const uint8_t PINxn, volatile uint8_t *PORTx, volatile uint8_t *DDRx, volatile uint8_t *PINx);
  Port(const Port& orig);
  ~Port();
  void setInput();
  void setOutput();
  void setHIGH();
  void setLOW();
  void toggle();
  bool isHIGH();
  void flash(const int ms);

private:
  const uint8_t Pxn;
  const uint8_t PINxn;
  volatile uint8_t *PORTx;
  volatile uint8_t *DDRx;
  volatile uint8_t *PINx;

  
  
};

#endif /* PORT_H */

