/*
 * STPMR.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Salem Elfaidy
 */
#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/DIO/DIO.h"
#include "STPMR.h"

u16 waiting = 500;
void STP_voidInit(void){

	DIO_voidSetPinDirection(STP_PORT, STP_COIL_BLUE,   DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_PINK,   DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_YELLOW, DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_ORANGE, DIO_OUTPUT);

}


void STP_voidRotateCW(void){

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(waiting);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(waiting);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(waiting);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_HIGH);
	_delay_ms(waiting);

}


void STP_voidRotateACW(void){

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_HIGH);
	_delay_ms(500);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(500);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(500);

	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_HIGH);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	_delay_ms(500);

}


