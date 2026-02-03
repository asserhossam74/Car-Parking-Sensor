/*
 * lcd.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Asser El-Hossary
 */

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"


/*----------------------------------------------Definitions-------------------------------------------------*/


/*Number of rows in the LCD*/
#define LCD_MAX_ROWS 2

#if((LCD_MAX_ROWS != 1) && (LCD_MAX_ROWS!= 2) && (LCD_MAX_ROWS!= 4) )

#error "Number of LCD_MAX_ROWS should be equal to 1or 2 or 4"

#endif


/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 4

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif


#define FIRST_COL 0           /** Defines the starting column index for the LCD display (0-based). */

#define LCD_MAX_COLS 16      /** Maximum number of columns supported by the LCD  */

/* LCD HW Ports and Pins Ids */
#define LCD_RS_PORT_ID                 PORTA_ID
#define LCD_RS_PIN_ID                  PIN1_ID

#define LCD_E_PORT_ID                  PORTA_ID
#define LCD_E_PIN_ID                   PIN2_ID

#define LCD_DATA_PORT_ID               PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID
#endif
/**--------------------------------------------LCD commands-------------------------------------------------*/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*---------------------------------------Types Declaration-------------------------------------------------*/
/*Enumeration representing the available rows on an LCD display*/
typedef enum
{
	FIRST_ROW=1,            /*First row of the LCD (typically Row 0 in physical terms)*/
	SECOND_ROW,            /* Second row of the LCD*/
	THIRD_ROW,            /*Third row of the LCD (only applicable for 4-row LCDs)*/
	FOURTH_ROW           /* Fourth row of the LCD (only applicable for 4-row LCDs)*/
}LCD_ROWS;
/*---------------------------------------function prototypes-----------------------------------------------*/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void);


/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data);


/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command);


/*
 * Description :
 * Display the required string on the LCD screen.
 * The function processes each character in the string, managing spaces and
 * ensuring words are displayed correctly without exceeding the current line's
 * width. If a word does not fit, it moves to the next line automatically.
 */
void LCD_displayString(const char *Str);


/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);


/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col);


/*
 * Description :
 * Move the cursor to the beginning of the specified row on the LCD.
 * This function checks the current row indicated by g_determineRow
 * and moves the cursor to the first column of that row.
 */
void LCD_moveCursorAutomaic(void);


/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);


/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);
#endif /* LCD_H_ */

