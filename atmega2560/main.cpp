/* 
 * File:   main.c
 * Author: Levin Messing
 *
 * Created on 11. Oktober 2017, 00:05
 */

#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>
#include <avr/iom2560.h>
#include <avr/sleep.h>
#include <util/delay.h>


struct PORT {
  uint8_t const port;
  volatile uint8_t *portRow;
  volatile uint8_t *ddr;

};

void sendChar(char *ch) {
  while ((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = *ch;
}

void sendCharField(char *field, int size) {
  for (int i = 0; i < size; i++)
    sendChar(&field[i]);
}

void toggleLED(const PORT *led) {
  *led->portRow ^= 1 << led->port;
}

void turnOnLED(const PORT *led) {
  *led->portRow |= 1 << led->port;
}

void turnOffLED(const PORT *led) {
  *led->portRow &= ~(1 << led->port);
}

void setOutput(const PORT *led) {
  *led->ddr |= 1 << led->port;
}

void setInput(const PORT *led) {
  *led->ddr &= ~(1 << led->port);
}

void flashLED(const PORT *led) {


  for (int i = 0; i < 50; i++) {
    toggleLED(led);
    _delay_ms(50);
  }

  turnOnLED(led);

}

void blink() {
  const PORT led1 = {PB7, &PORTB, &DDRB};
  const PORT led2 = {PB6, &PORTB, &DDRB};

  setOutput(&led1);
  setOutput(&led2);


  flashLED(&led1);
  flashLED(&led2);

}

void uart() {
  //Set Baudrate to 1000000 (1 Mbit)
  if (U2X0 == 1)
    UBRR0 = 0;



  //  char lol[4] = "LoL";
  //
  //  char str = 'G';
  //  char str2 = 'O';
  //
  //  sendChar(&str);
  //  sendChar(&str);
  //
  //  sendChar(&str);
  //  sendChar(&str);
  //
  //
  //  sendCharField(lol, sizeof (lol) / sizeof (char));


  //char nl = '\n';
  //sendChar(&nl);
}

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

bool isHIGH(const PORT *input) {



  if ((PINB & (1 << PINB5)) == (1 << PINB5))
    return true;
  else
    return false;

}

volatile bool flag1;

ISR(INT0_vect) {
  flag1 = true;
}

/*
 * 
 */
int main() {
  //blink();
  uart();


  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  EIMSK |= (1 << INT0);
  //SREG |= (1 << SREG_I);


  const PORT led1 = {PB4, &PORTB, &DDRB};
  const PORT input = {PB5, &PORTB, &DDRB};
  const PORT ISRinput = {PD0, &PORTD, &DDRD};

  setInput(&ISRinput);
  turnOnLED(&ISRinput);
  setOutput(&led1);
  setInput(&input);


  sei();

  while (true) {

    char str[20] = "Start\n\r";
    sendCharField(str, sizeof (str) / sizeof (char));


    goToSleep();

    if (flag1) {
      blink();


      cli();
      flag1 = false;
      sei();
    }

    _delay_ms(500);

  };







  return (EXIT_SUCCESS);
}

