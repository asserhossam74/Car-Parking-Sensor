/************************************************************************************************************
 *
 * Module: Parking Sensor
 *
 * File Name: parking_sensor.c
 *
 * Author: Asser El-Hossary
 *
 ***********************************************************************************************************/
#include "icu.h"
#include "ultrasonic_sensor.h"
#include "lcd.h"
#include "buzzer.h"
#include "led.h"
#include <util/delay.h>
#include <avr/io.h>

/*----------------------------------------------global variables-------------------------------------------*/
uint16 g_distance_by_sensor = 0;

/*--------------------------------------------Function prototypes----------------------------------------- */
void driversInitialization(void);

int main()
{
    SREG |= (1 << 7); /* Enable global interrupts */
    driversInitialization();
    /* Display initial message on the LCD */
    LCD_displayString("Distance = ");

    while (1)
    {
        /* Read distance from the ultrasonic sensor */
        g_distance_by_sensor = Ultrasonic_readDistance();

        /* Check if the distance is less than or equal to 5 cm */
        if (g_distance_by_sensor <= 5)
        {
            /* Display distance on the LCD */
            LCD_moveCursor(FIRST_ROW, 11);
            LCD_intgerToString(g_distance_by_sensor);
            LCD_displayCharacter(' ');  /* Clear any extra characters */
            LCD_moveCursor(SECOND_ROW, 6);
            LCD_displayString("Stop");

            if (g_distance_by_sensor == 5)
            {
                Buzzer_on();                /* Activate buzzer */
                LED_allLedsOn();           /* Turn on all LEDs */
                _delay_ms(150);
                Buzzer_off();
                LED_allLedsOff();          /* Turn off all LEDs */
                _delay_ms(150);
            }
            else if (g_distance_by_sensor == 4)
            {
                Buzzer_on();                /* Activate buzzer */
                LED_allLedsOn();           /* Turn on all LEDs */
                _delay_ms(80);
                Buzzer_off();
                LED_allLedsOff();          /* Turn off all LEDs */
                _delay_ms(80);
            }
            else
            {
                Buzzer_on();                /* Activate buzzer */
                LED_allLedsOn();           /* Turn on all LEDs */
            }
        }
        else  /* If the distance is greater than 5 cm*/
        {
            Buzzer_off();              /* Deactivate buzzer */
            LCD_moveCursor(SECOND_ROW, 6);
            LCD_displayString("    ");  /* Clear the stop message */
        }

        /* Distance ranges handling */
        if (g_distance_by_sensor >= 6 && g_distance_by_sensor <= 10)
        {
            LED_allLedsOn();          /* Turn on all LEDs for warning */
            LCD_moveCursor(FIRST_ROW, 11);
            LCD_intgerToString(g_distance_by_sensor);
            if (g_distance_by_sensor < 10)
            {
                LCD_displayCharacter(' '); /* Clear any extra character */
            }
        }
        else if (g_distance_by_sensor >= 11 && g_distance_by_sensor <= 15)
        {
            LED_off(BLUE_LED);       /* Turn off the blue LED */
            LED_on(RED_LED);         /* Turn on the red LED */
            LED_on(GREEN_LED);       /* Turn on the green LED */
            LCD_moveCursor(FIRST_ROW, 11);
            LCD_intgerToString(g_distance_by_sensor);
        }
        else if (g_distance_by_sensor >= 16 && g_distance_by_sensor <= 20)
        {
            LED_off(BLUE_LED);       /* Turn off the blue LED */
            LED_off(GREEN_LED);      /* Turn off the green LED */
            LED_on(RED_LED);         /* Keep red LED on */
            LCD_moveCursor(FIRST_ROW, 11);
            LCD_intgerToString(g_distance_by_sensor);
        }
        else if (g_distance_by_sensor > 20)
        {
            LED_allLedsOff();        /* Turn off all LEDs */
            LCD_moveCursor(FIRST_ROW, 11);
            LCD_intgerToString(g_distance_by_sensor);
        }

        /* Display distance units */
        if (g_distance_by_sensor < 10)
        {
            LCD_moveCursor(FIRST_ROW, 13);
            LCD_displayString("CM");
            LCD_displayCharacter(' ');
        }
        else
        {
            LCD_moveCursor(FIRST_ROW, 13);
            LCD_displayCharacter(' ');
            LCD_moveCursor(FIRST_ROW, 14);
            LCD_displayString("CM");
        }
    }
}

/*****************************************************
 * Function:
 *  Initializes all drivers required for the parking sensor system.
 *  return: none
 ******************************************************/
void driversInitialization(void)
{
    static ICU_ConfigType ICU_data = {F_CPU_8, RAISING}; /* Configuration for ICU */
    ICU_init(&ICU_data);           /* Initialize the ICU */
    LEDS_init();                   /* Initialize LEDs */
    LCD_init();                    /* Initialize LCD */
    Ultrasonic_init();             /* Initialize ultrasonic sensor */
    Buzzer_init();                 /* Initialize buzzer */
}
