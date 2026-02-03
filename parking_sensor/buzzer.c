/*
 * buzzer.c
 *
 *  Created on: Oct 3, 2024
 *      Author: Asser El-Hossary
 */

#include"buzzer.h"
#include"gpio.h"

/*************************************************************
 * Description : Initialize the buzzer by setting its direction
 * in output direction and  turning of the buzzer
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_init(void)
{
	/*make it output direction*/
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	/*make buzzer off*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

/*************************************************************
 * Description : function to set buzzer on
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*************************************************************
 * Description : function to set buzzer off
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
