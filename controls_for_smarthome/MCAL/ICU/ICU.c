/*
 * ICU.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Salem Elfaidy
 */
#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ICU.h"


void (*ICU_pf) (void);


void ICU_voidInit (void){

	/* Select Timer1 Normal Mode */
	CLR_BIT(TCCR1A, WGM10);
	CLR_BIT(TCCR1A, WGM11);
	CLR_BIT(TCCR1B, WGM12);
	CLR_BIT(TCCR1B, WGM13);

	/* Prescaler (8) */
	TCCR1B &= 0b11111000;
	TCCR1B |= 0b00000010;

	/* enable interrupt */
	SET_BIT(TIMSK, TICIE1);

	/* select trigger(Rising) */
	SET_BIT(TCCR1B, ICES1);

}


void ICU_voidChangeTrigger	 (u8 Copy_u8Trigger){

	switch (Copy_u8Trigger) {
		case ICU_FALLING_EDGE: CLR_BIT(TCCR1B, ICES1);	break;
		case ICU_RISING_EDGE:  SET_BIT(TCCR1B, ICES1);	break;
	}

}


void ICU_voidSetCallback  	(void (*Copy_pf) (void)){

	ICU_pf = Copy_pf;

}


u16	 ICU_u16ReadValue (void){

	return ICR1;
}


void ICU_voidDisableInterrupt(void){

	/* disable interrupt */
	CLR_BIT(TIMSK, TICIE1);

}


ISR(TIMER1_CAPT_vect){

	ICU_pf();

}
