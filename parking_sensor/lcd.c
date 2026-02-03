/*
 * lcd.c
 *
 * Created on: Sep 30, 2024
 * Author: Asser El-Hossary
 */

#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>
#include <stdlib.h>
#include "common_macros.h"

/* Current position of the cursor on the LCD.
 * It is initialized to 0, indicating the start of the line. */
static uint8 g_currentPosition = FIRST_COL;

/* Keeps track of the current row being displayed on the LCD.
 * Initialized to FIRST_ROW to start displaying from the top row. */
static uint8 g_determineRow = FIRST_ROW;

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions using the GPIO driver.
 * 2. Setup the LCD Data Mode: 4-bits or 8-bits.
 */
void LCD_init(void)
{
    /* Configure the direction for RS and E pins as output pins. */
    GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
    _delay_ms(20);

#if (LCD_DATA_BITS_MODE == 4)
    /* Make 4 pins in data port as output pins. */
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID , PIN_OUTPUT);
    /* Send for 4-bit initialization of LCD. */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
    /* Use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode. */
    LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#elif (LCD_DATA_BITS_MODE == 8)
    /* Configure the data port as output port. */
    GPIO_setupPortDirection(LCD_DATA_PORT_ID, PIN_OUTPUT);
    /* Use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode. */
    LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

    LCD_sendCommand(LCD_CURSOR_OFF); /* Cursor off. */
    LCD_sendCommand(LCD_CLEAR_COMMAND); /* Clear LCD at the beginning. */
}

/*
 * Description :
 * Display the required character on the screen.
 */
void LCD_displayCharacter(uint8 data)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 7));

    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
    _delay_ms(1); /* Delay for processing Th = 13ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1. */
    _delay_ms(1); /* Delay for processing Tpw - Tdws = 190ns. */

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data, 3));

    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
#elif (LCD_DATA_BITS_MODE == 8)
    GPIO_writePort(LCD_DATA_PORT_ID, data);
    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
#endif

    _delay_ms(1); /* Delay for processing Th = 13ns. */

    g_currentPosition++; /* Update the position for each character printed. */
}

/*
 * Description :
 * Send the required command to the screen.
 */
void LCD_sendCommand(uint8 command)
{
    GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
    _delay_ms(1);

#if (LCD_DATA_BITS_MODE == 4)
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 7));

    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
    _delay_ms(1); /* Delay for processing Th = 13ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH); /* Enable LCD E=1. */
    _delay_ms(1); /* Delay for processing Tpw - Tdws = 190ns. */

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command, 0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command, 1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command, 2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command, 3));

    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
#elif (LCD_DATA_BITS_MODE == 8)
    GPIO_writePort(LCD_DATA_PORT_ID, command);
    _delay_ms(1); /* Delay for processing Tdsw = 100ns. */
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW); /* Disable LCD E=0. */
#endif

    _delay_ms(1); /* Delay for processing Th = 13ns. */
}

/*
 * Description :
 * Display the required string on the LCD screen.
 * The function processes each character in the string, managing spaces and
 * ensuring words are displayed correctly without exceeding the current line's
 * width. If a word does not fit, it moves to the next line automatically.
 */
void LCD_displayString(const char *Str)
{
    uint8 counter = 0;                          /* Counter for traversing the input string. */
    const char *ptrHoldString = Str;   /*Pointer initialized to the start of the input string for word processing*/
    uint8 length = 0;                        /* Length of the current word being processed. */
    /* Index for traversing the characters of the current word when printing it to the LCD*/
    uint8 counter_2 = 0;



    /* Loop through the string until reaching null. */
    while (Str[counter] != '\0')
    {
        if (Str[counter] != ' ') /* Check if the current character is not a space. */
        {
            length++; /* Increase the length count for the current word. */
        }
        else /* When we hit a space. */
        {
            if ((length + g_currentPosition) > LCD_MAX_COLS) /* Check if the word fits in the current line. */
            {
                g_determineRow++; /* Move to the next line. */
                LCD_moveCursorAutomaic(); /* Move cursor to the start of the new line. */
                g_currentPosition = 0; /* Reset the position for the new line. */

            }

            /* Now print the previous word. */
            for (counter_2 = 0; counter_2 < length; counter_2++)
            {
                LCD_displayCharacter(ptrHoldString[counter_2]); /* Print each character of the word. */
            }

            /* Prepare for the next word. */
            ptrHoldString = Str + counter + 1; /* Set the pointer to the start of the next word. */
            counter_2 = 0;
            length = 0; /* Reset length for the next word. */

            /* Print the space. */
            LCD_displayCharacter(' ');
        }
        counter++; /* Move to the next character in the string. */
    }

    /* Print the last word if there's any. */
    if (length > 0)
    {
        if ((length + g_currentPosition) > LCD_MAX_COLS)
        {
        	g_determineRow++;
            LCD_moveCursorAutomaic();
            g_currentPosition = 0;
        }

        for (counter_2 = 0; counter_2 < length; counter_2++)
        {
            LCD_displayCharacter(ptrHoldString[counter_2]); /* Print each character of the last word. */
        }
    }
}


/*
 * Description :
 * Display the required decimal value on the screen.
 */
void LCD_intgerToString(int data)
{
    char buff[LCD_MAX_COLS]; /* String to hold the ASCII result. */
    itoa(data, buff, 10); /* Convert the data to its corresponding ASCII value. */
    LCD_displayString(buff); /* Display the string. */
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen.
 * This function is made for screens: 2x16 and 4x16.
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
    uint8 lcd_memory_address;

    /* Calculate the required address in the LCD DDRAM. */
    switch (row)
    {
        case (FIRST_ROW):
            lcd_memory_address = col;
            break;

#if (LCD_MAX_ROWS >= 2)
        case (SECOND_ROW):
            lcd_memory_address = col + 0x40;
            break;
#endif

#if (LCD_MAX_ROWS == 4)
        case (THIRD_ROW):
            lcd_memory_address = col + 0x10;
            break;

        case (FOURTH_ROW):
            lcd_memory_address = col + 0x50;
            break;
#endif
    }
    g_currentPosition=col;
    LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Move the cursor to the beginning of the specified row on the LCD.
 * This function checks the current row indicated by g_determineRow
 * and moves the cursor to the first column of that row.
 */
void LCD_moveCursorAutomaic(void)
{
	/* Check if the current row is the second row*/
    if (g_determineRow == SECOND_ROW)
    {
    	 /* Move the cursor to the first column of the second row*/
        LCD_moveCursor(SECOND_ROW, FIRST_COL);
    }

    /* If the LCD has four rows*/
#if (LCD_MAX_ROWS == 4)
    /* Check if the current row is the third row*/
    if (g_determineRow == THIRD_ROW)
    {
    	 /* Move the cursor to the first column of the third row*/
        LCD_moveCursor(THIRD_ROW, FIRST_COL);
    }
    /* Check if the current row is the fourth row*/
    else if (g_determineRow == FOURTH_ROW)
    {
    	 /* Move the cursor to the first column of the fourth row*/
        LCD_moveCursor(FOURTH_ROW, FIRST_COL);
    }
#endif
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen.
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
	g_currentPosition=col;
    LCD_moveCursor(row, col); /* Go to the required LCD position. */
    LCD_displayString(Str); /* Display the string. */
}

/*
 * Description :
 * Send the clear screen command.
 */
void LCD_clearScreen(void)
{
    LCD_sendCommand(LCD_CLEAR_COMMAND);
    g_determineRow = FIRST_ROW; /* Reset row tracker after clearing the screen. */

}

