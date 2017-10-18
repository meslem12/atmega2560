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
#include "jsmn.h"

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

void initTimer() {
  //set as CTC
  TCCR0A |= 1 << WGM01;
  //set prescale 64
  TCCR0B |= (1 << CS00) | (1 << CS01);
  //set TOP to 124
  OCR0A = 249;
  //enable interrupt
  TIMSK0 |= 1 << OCIE0A;

}



int timerFlag = 0;
int ms = 0;
int s = 0;
int min = 0;

ISR(TIMER0_COMPA_vect) {
  timerFlag++;
}

/*
 * 
 */
int main() {

  UART uart;
  Port led_1(PB7, PINB7, &PORTB, &DDRB, &PINB);
  initTimer();
  led_1.setOutput();
  led_1.setLOW();

  jsmn_parser parser;
  jsmn_init(&parser);

  jsmntok_t tokens[256];
  const char *js;
  js = "{\"glossary\":{\"title\":\"example glossary\",\"GlossDiv\":{\"title\":\"S\",\"GlossList\":{\"GlossEntry\":{\"ID\":\"SGML\",\"SortAs\":\"SGML\",\"GlossTerm\":\"Standard Generalized Markup Language\",\"Acronym\":\"SGML\",\"Abbrev\":\"ISO 8879:1986\",\"GlossDef\":{\"para\":\"A meta-markup language, used to create markup languages such as DocBook.\",\"GlossSeeAlso\":[\"GML\",\"XML\"]},\"GlossSee\":\"markup\"}}}}}";

  jsmn_parse(&parser, js, strlen(js), tokens, 256);
  
  
  
  

uart.sendChar("Program start\n");


sei();


while (1) {

  cli();
  while (timerFlag > 0) {
    timerFlag--;
    sei();
    ms++;
    if (ms >= 1000) {
      ms = 0;
      s++;
    }
    if (s >= 60) {
      s = 0;
      min++;
    }
    if (min >= 100) {
      min = 0;
    }
    cli();
  }
  sei();

  char time[30];

  snprintf(time, sizeof (time) / sizeof (char), "%02d - %02d - %03d\r", min, s, ms);
  uart.sendChar(time);
}


return (0);
}

