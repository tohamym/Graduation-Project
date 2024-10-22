/*
 * main.c
 *
 *  Created on: Sep 2, 2023
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include "LIB/BIT_Math.h"
#include "LIB/STD_Types.h"
#include "MCAL/DIO/DIO.h"
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/INT/INT.h"
#include <avr/interrupt.h>
#include "MCAL/ADC/ADC.h"
#include "HAL/Stepper_Motor/STPMR.h"
#include "MCAL/TIMER0/TIM0.h"
#include "MCAL/SPI/SPI.h"


		/************* SLAVE **************/
int main(void){

	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_INPUT);	// ss
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_INPUT);	// MOSI
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_OUTPUT);	// MISO
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_INPUT);	// CK
	_delay_ms(200);
	SPI_voidInit();
	_delay_ms(200);

	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN0, DIO_OUTPUT); //NIGHT LIGHT

	/* ADC */
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN0, DIO_INPUT);
	ADC_voidInit(ADC_DIV_64);

	STP_voidInit();

	u16 Local_u16DigitalVlaueLDR, Local_u16AnaloglValueLDR;
	u16 Local_u16DigitalVlaueTEMP, Local_u16AnaloglValueTEMP;



	while(1){
		u8 Local_u8TempFlag = 'z';
		u8 Local_u8NightLightFlag = 'z';
		u8 Local_u8SPIDataReceived = SPI_u8ReceiveData();

		/* TEMP Sensor (always on) */
		Local_u16DigitalVlaueTEMP = ADC_u16GetDigitalValue(ADC_Channel_1);
		Local_u16AnaloglValueTEMP = (Local_u16DigitalVlaueTEMP * 5000UL)/1024;

		/* fire alarm (always on)*/
		if(Local_u16AnaloglValueTEMP >= 570){
			Local_u8TempFlag = 'A';
			Local_u8NightLightFlag = 'A';
			//SPI_voidSalveSendData('l'); //l for alarm
			Local_u8SPIDataReceived = 'x'; //x is arbitrary constant
		}

		if(Local_u8SPIDataReceived == 'c'){ //received correct login


			/* LDR */
			Local_u16DigitalVlaueLDR = ADC_u16GetDigitalValue(ADC_Channel_0);
			Local_u16AnaloglValueLDR = (Local_u16DigitalVlaueLDR * 5000UL)/1024;

			/* NIGHT LIGTH */
			if(Local_u16AnaloglValueLDR <= 1500){
				DIO_voidSetPinValue(DIO_PORTC, DIO_PIN0, DIO_LOW);
				Local_u8NightLightFlag = '0';
			}
			else if(Local_u16AnaloglValueLDR > 1500 ){
				DIO_voidSetPinValue(DIO_PORTC, DIO_PIN0, DIO_HIGH);
				Local_u8NightLightFlag = '1';
			}

			/* AC Unit */
			if(Local_u16AnaloglValueTEMP <= 200){
				STP_voidRotate(STP_SPEED_1,STP_DIRECTION_CW);
				Local_u8TempFlag = '1';
			}
			else if((Local_u16AnaloglValueTEMP > 200)&&(Local_u16AnaloglValueTEMP <= 300)){
				STP_voidRotate(STP_SPEED_2,STP_DIRECTION_CW);
				Local_u8TempFlag = '2';
			}
			else if((Local_u16AnaloglValueTEMP > 300)&&(Local_u16AnaloglValueTEMP < 570)){
				STP_voidRotate(STP_SPEED_3, STP_DIRECTION_CW);
				Local_u8TempFlag = '3';
			}
			else{
				//
			}
		}else{ //wrong password
			DIO_voidSetPinValue(DIO_PORTC, DIO_PIN0, DIO_LOW); //NIGHT_LIGTH off
			STP_voidOff();										//AC unit off
		}

		switch(Local_u8NightLightFlag){
			case 'A':
				SPI_voidSalveSendData('A');
			break;
			case '0':
				switch(Local_u8TempFlag){
					case '1': SPI_voidSalveSendData('1'); break;
					case '2': SPI_voidSalveSendData('2'); break;
					case '3': SPI_voidSalveSendData('3'); break;
				}
			break;
			case '1':
				switch(Local_u8TempFlag){
					case '1': SPI_voidSalveSendData('4'); break;
					case '2': SPI_voidSalveSendData('5'); break;
					case '3': SPI_voidSalveSendData('6'); break;
				}

			break;
		}
	}
	return 0;
}
