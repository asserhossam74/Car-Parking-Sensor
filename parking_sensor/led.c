/*
 * led.c
 *
 *  Created on: Oct 4, 2024
 *      Author: Asser El-Hossary
 */

#include"led.h"
#include"std_types.h"
/*****************************************************
 * Definition:
 *  Initializes all Leds  pins direction.
 *  Turn off all the Leds
 *  return:none
 *  function argument:none
 ******************************************************/
void LEDS_init(void)
{
	/*make all leds in output direction*/
	GPIO_setupPinDirection(RED_LED_PORT_ID ,RED_LED_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,PIN_OUTPUT);

/*check if it is positive logic or negative logic*/
#if(POSTIVE_LOGIC_CONECTION)
	GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_LOW);
	GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_LOW);
	GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_LOW);

#elif(NEGATIVE_LOGIC_CONECTION )
	GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_HIGH);
#endif
}

/*****************************************************
 * Definition:
 *  Turns on the specified LED.
 *  return:none
 *  function argument:none
 ******************************************************/
 void LED_on(LED_ID id)
 {
	 /*check if it is positive logic or negative logic*/
#if(POSTIVE_LOGIC_CONECTION)
	 /*switch case to check the coming led*/
	 switch(id)
	 {
	 case RED_LED:
		 GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 case GREEN_LED:
		 GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 case BLUE_LED:
	   	 GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 }

#elif(NEGATIVE_LOGIC_CONECTION )

	 switch(id)
	 {
	 case RED_LED:
		 GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_LOW);
		 break;
	 case GREEN_LED:
		 GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_LOW);
		 break;
	 case BLUE_LED:
	   	 GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_LOW);
		 break;
	 }


#endif
 }

 /*****************************************************
  * Definition:
  *   Turns off the specified LED.
  *  return:none
  *  function argument:none
  ******************************************************/
 void LED_off(LED_ID id)
 {
	 /*check if it is positive logic or negative logic*/
#if(POSTIVE_LOGIC_CONECTION)
	 switch(id)
	 {
	 case RED_LED:
		 GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_LOW);
		 break;
	 case GREEN_LED:
		 GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_LOW);
		 break;
	 case BLUE_LED:
	   	 GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_LOW);
		 break;
	 }

#elif(NEGATIVE_LOGIC_CONECTION )

	 switch(id)
	 {
	 case RED_LED:
		 GPIO_writePin(RED_LED_PORT_ID ,RED_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 case GREEN_LED:
		 GPIO_writePin(GREEN_LED_PORT_ID ,GREEN_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 case BLUE_LED:
	   	 GPIO_writePin(BLUE_LED_PORT_ID ,BLUE_LED_PIN_ID,LOGIC_HIGH);
		 break;
	 }


#endif
 }


 /*****************************************************
  * Definition:
  *  Turns on all LEDs sequentially.
  *  return: none
  *  function argument: none
  ******************************************************/
 void LED_allLedsOn(void)
 {
	 uint8 counter;
	 for(counter=0;counter<NUMBER_OF_LEDS;counter++)
	 {
		 LED_on(counter);
	 }
 }

 /*****************************************************
  * Definition:
  *  Turns off all LEDs sequentially.
  *  return: none
  *  function argument: none
  ******************************************************/
 void LED_allLedsOff(void)
 {
	 uint8 counter;
	 for(counter=0;counter<NUMBER_OF_LEDS;counter++)
	 {
		 LED_off(counter);
	 }
 }
