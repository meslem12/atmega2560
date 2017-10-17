/* 
 * File:   main.c
 * Author: Levin Messing
 *
 * Created on 11. Oktober 2017, 00:05
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
//#include <avr/iom2560.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "UART.h"
#include "Port.h"




void setSleepMode() {
  SMCR |= SLEEP_MODE_PWR_DOWN;
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void goToSleep() {

  SMCR |= (1 << SE);
  sleep_enable();

  sleep_cpu();

  sleep_disable();
  SMCR &= ~(1 << SE);
}


volatile bool flag1;

//ISR(INT0_vect) {
//  flag1 = true;
//}

void interruptAndSleep() {



  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  EIMSK |= (1 << INT0);
 
  sei();

}

void setUpPWM() {
  TCCR0B |= (1 << CS00);
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
}

void PWM() {

  setUpPWM();

  OCR0A = 0;

  while (1) {
    for (int i = 10; i < 200; i++) {
      OCR0A = i;
      _delay_ms(20);
    }
    for (int i = 200; i > 10; i--) {
      OCR0A = i;
      _delay_ms(20);
    }

  }

}


/*
 * 
 */
int main() {
  
  UART uart;
  Port led_1(PB7, PINB7, &PORTB, &DDRB, &PINB);
  
  uart.sendChar("Program start\n");
  _delay_ms(1000);
  
  led_1.setOutput();
  led_1.setLOW();
  
  
  while(1)
  {
    
    char input = {uart.getChar()};

    uart.sendChar(input);
    uart.sendChar('\n');
  }
  
  
  
  return (0);
}

