#include "icu.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	DDRD &= ~(1 << PD6);  // Configure ICP1/PD6 as input pin

	TCCR1A = (1 << FOC1A) | (1 << FOC1B);  // Timer1 in Normal Mode

	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << 6);

	TCNT1 = 0;  // Initial Value for Timer1
	ICR1 = 0;   // Initial Value for the input capture register

	TIMSK |= (1 << TICIE1);  // Enable Input Capture interrupt
}

void ICU_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;  // Save the address of the Call back function
}

void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (edgeType << 6);
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;  // Return the value stored in ICR1
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;  // Clear Timer1
}

void ICU_deInit(void)
{
	TCCR1A = 0;  // Clear all Timer1/ICU Registers
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	TIMSK &= ~(1 << TICIE1);  // Disable the Input Capture interrupt
	g_callBackPtr = NULL_PTR;  // Reset the global pointer
}

