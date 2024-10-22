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
#include "../../MCAL/TIMER0/TIM0.h"
#include <avr/interrupt.h>

u16 Global_Speed;
u8 Global_direction;



void STP_voidInit(void){

	TIM0_voidInit();
	/* 8 Ms/ 8 >> 1M HZ >> tick time = 1/ 1M  = 1 Micro second >> overflow time = 256 * tick time = 256 micro sec  */
	/* 1/ (256 micro sec) = 3906.25 */
	/* ((0.25) * 256) = 64 >>> 256 - 64 = 192 */
	TIM0_voidTimerStart(TIM0_PRESCALER_8);
	sei();
	TIM0_voidOvrINTControl(TIM0_TIN_EABLE);
	TIM0_voidOvfCallback(Rotate);

	DIO_voidSetPinDirection(STP_PORT, STP_COIL_BLUE,   DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_PINK,   DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_YELLOW, DIO_OUTPUT);
	DIO_voidSetPinDirection(STP_PORT, STP_COIL_ORANGE, DIO_OUTPUT);

}

//1 sec is 3906.25
void STP_voidRotate(u8 Copy_u8Speed, u8 Copy_u8Direction){
	if(Copy_u8Speed == STP_SPEED_1){
		Global_Speed = 12000; //equivlent of waiting for ~750 ms
	}
	else if(Copy_u8Speed == STP_SPEED_2){
		Global_Speed = 8000; //equivlent of waiting for ~500 ms
	}
	else if(Copy_u8Speed == STP_SPEED_3){
		Global_Speed = 4000; //equivlent of waiting for ~250 ms
	}
	Global_direction = Copy_u8Direction;

}

void Rotate(void){
	if(Global_direction == STP_DIRECTION_CW){
		RotateCW();
	}
	if(Global_direction == STP_DIRECTION_ACW){
		RotateACW();
	}
	if(Global_direction == STP_OFF){
		OFF();
	}
}

void RotateCW(void){

	static u16 Local_u16Count =0;
	if(Local_u16Count <= (Global_Speed/4)){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if((Local_u16Count > (Global_Speed/4))&&(Local_u16Count <= (Global_Speed/2))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if((Local_u16Count > (Global_Speed/2))&&(Local_u16Count <= (Global_Speed*3/4))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if((Local_u16Count > (Global_Speed*3/4))&&(Local_u16Count < (Global_Speed))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_HIGH);
	}
	else if(Local_u16Count == Global_Speed){
		Local_u16Count = 0;
	}

	Local_u16Count++;
}

void RotateACW(void){
	static u16 Local_u16Count =0;
	if(Local_u16Count <= (Global_Speed/4)){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_HIGH);
	}
	else if((Local_u16Count > (Global_Speed/4))&&(Local_u16Count <= (Global_Speed/2))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if((Local_u16Count > (Global_Speed/2))&&(Local_u16Count <= (Global_Speed*3/4))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if((Local_u16Count > (Global_Speed*3/4))&&(Local_u16Count < (Global_Speed))){
		DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_HIGH);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
		DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
	}
	else if(Local_u16Count == Global_Speed){
		Local_u16Count = 0;
	}

	Local_u16Count++;
}

void STP_voidOff(void){
	Global_direction = STP_OFF;
}

void OFF(void){
	DIO_voidSetPinValue(STP_PORT, STP_COIL_BLUE,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_PINK,   DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_YELLOW, DIO_LOW);
	DIO_voidSetPinValue(STP_PORT, STP_COIL_ORANGE, DIO_LOW);
}
