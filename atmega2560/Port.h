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


class Port {
  
public:
  Port();
  Port(uint8_t Pxn, volatile uint8_t *PORTx, volatile uint8_t *DDRx, volatile uint8_t *PINx);
  Port(const Port& orig);
  ~Port();
private:

};

#endif /* PORT_H */

