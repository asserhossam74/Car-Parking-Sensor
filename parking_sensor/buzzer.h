/*
 * buzzer.h
 *
 *  Created on: Oct 3, 2024
 *      Author: Asser El-Hossary
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/**define  port that buzzer connected to it*/
#define BUZZER_PORT_ID PORTC_ID
/**define  pin that buzzer connected to*/
#define BUZZER_PIN_ID  PIN5_ID


/*************************************************************
 * Description : Initialize the buzzer by setting its direction
 * in output direction and  turning of the buzzer
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_init(void);

/*************************************************************
 * Description : function to set buzzer on
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_on(void);

/*************************************************************
 * Description : function to set buzzer off
 * Argument    : None
 * Returns     : None
 *************************************************************/
void Buzzer_off(void);

#endif /* BUZZER_H_ */
