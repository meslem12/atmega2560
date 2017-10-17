/* 
 * File:   Port.cpp
 * Author: Levin Messing <levin@inode.at>
 * 
 * Created on 16. Oktober 2017, 18:46
 */

#include "Port.h"

Port::Port(const uint8_t Pxn, const uint8_t PINxn, volatile uint8_t *PORTx, volatile uint8_t *DDRx, volatile uint8_t *PINx)
: Pxn(Pxn),
PINxn(PINxn),
PORTx(PORTx),
DDRx(DDRx),
PINx(PINx) {
}

Port::Port(const Port& orig)
: Pxn(orig.Pxn),
PINxn(PINxn),
PORTx(orig.PORTx),
DDRx(orig.DDRx),
PINx(orig.PINx) {

}

Port::~Port() {
}

void Port::setInput() {
  *DDRx &= ~(1 << Pxn);
}

void Port::setOutput() {
  *DDRx |= 1 << Pxn;
}

void Port::setHIGH() {
  *PORTx |= 1 << Pxn;
}

void Port::setLOW() {
  *PORTx &= ~(1 << Pxn);
}

void Port::toggle() {
  *PORTx ^= 1 << Pxn;
}

bool Port::isHIGH() {
  if ((*PINx & (1 << PINxn)) == (1 << PINxn))
    return true;
  else
    return false;
}

void Port::flash(const int ms) {

  if(ms<100)
    return;
  
  setHIGH();
  
  for (int i = 0; i < ms/50; i++) {
    toggle();
    _delay_ms(50);
  }

  setLOW();
}

