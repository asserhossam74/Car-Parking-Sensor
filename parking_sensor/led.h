/*
 * led.h
 *
 *  Created on: Oct 4, 2024
 *      Author: Asser El-Hossary
 */

#ifndef LED_H_
#define LED_H_

#include"gpio.h"

/*--------------------------------------------type declaration-----------------------------------------------*/
typedef enum
{
	RED_LED,
	GREEN_LED,
	BLUE_LED
}LED_ID;
/*---------------------------------------------definitions--------------------------------------------------*/
#define RED_LED_PORT_ID                     PORTC_ID
#define GREEN_LED_PORT_ID                   PORTC_ID
#define BLUE_LED_PORT_ID                    PORTC_ID
#define RED_LED_PIN_ID					    PIN0_ID
#define GREEN_LED_PIN_ID					PIN1_ID
#define BLUE_LED_PIN_ID						PIN2_ID
/*if you want positive logic put it one and negative logic 0 and vice versa*/
#define POSTIVE_LOGIC_CONECTION				1
#define NEGATIVE_LOGIC_CONECTION            0
/*define number of leds you used*/
#define NUMBER_OF_LEDS 3
/*----------------------------------------function prototypes-----------------------------------------------*/


/*****************************************************
 * Definition:
 *  Initializes all Leds  pins direction.
 *  Turn off all the Leds
 *  return:none
 *  function argument:none
 ******************************************************/
void LEDS_init(void);


/*****************************************************
 * Definition:
 *  Turns on the specified LED.
 *  return:none
 *  function argument:none
 ******************************************************/
 void LED_on(LED_ID id);


 /*****************************************************
  * Definition:
  *   Turns off the specified LED.
  *  return:none
  *  function argument:none
  ******************************************************/
 void LED_off(LED_ID id);

 /*****************************************************
  * Definition:
  *  Turns on all LEDs sequentially.
  *  return: none
  *  function argument: none
  ******************************************************/
 void LED_allLedsOn(void);

 /*****************************************************
  * Definition:
  *  Turns off all LEDs sequentially.
  *  return: none
  *  function argument: none
  ******************************************************/
 void LED_allLedsOff(void);

#endif /* LED_H_ */
