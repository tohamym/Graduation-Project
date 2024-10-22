/*
 * SSD.c
 *
 *  Created on: Aug 18, 2023
 *      Author: onetw
 */

#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL//DIO/DIO.h"
#include "SSD.h"



void SSD_voidInit(void){
	DIO_voidSetPortDirection(SSD_PORT,DIO_OUTPUT_PORT);
}

void SSD_voidKPDToSSD(u8 Copy_u8Char){
	switch(Copy_u8Char){
	case '0': DIO_voidSetPortValue(SSD_PORT,ZERO); break;
	case '1': DIO_voidSetPortValue(SSD_PORT,ONE); break;
	case '2': DIO_voidSetPortValue(SSD_PORT,TWO); break;
	case '3': DIO_voidSetPortValue(SSD_PORT,THREE); break;
	case '4': DIO_voidSetPortValue(SSD_PORT,FOUR); break;
	case '5': DIO_voidSetPortValue(SSD_PORT,FIVE); break;
	case '6': DIO_voidSetPortValue(SSD_PORT,SIX); break;
	case '7': DIO_voidSetPortValue(SSD_PORT,SEVEN); break;
	case '8': DIO_voidSetPortValue(SSD_PORT,EIGHT); break;
	case '9': DIO_voidSetPortValue(SSD_PORT,NINE); break;
	case 'C': DIO_voidSetPortValue(SSD_PORT,ZERO); break;
	default : DIO_voidSetPortValue(SSD_PORT,0b01001001); break;
	}
}
