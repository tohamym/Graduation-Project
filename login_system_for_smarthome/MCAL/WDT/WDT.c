/*
 * WDT.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Salem Elfaidy
 */

#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include <avr/io.h>
#include "WDT.h"

void WDT_voidEnable(u8 Copt_u8WaitingTime){

	/* enable watchdog */
	SET_BIT(WDTCR, WDE);

	/* select prescaler */
	WDTCR &= 0b11111000;
	WDTCR |= Copt_u8WaitingTime;

}


void WDT_voidDisable(void){

	/* Write logical one to WDTOE and WDE */
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
}

