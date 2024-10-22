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
#include "MCAL/TIMER0/TIM0.h"
#include "MCAL/SPI/SPI.h"

u8 Global_SPI_Flag ='0';
u8 Global_LCD_VIEW = '0';
void SPICommunication(void);

		/************* MASTER **************/
int main(void){


	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_OUTPUT);	// MOSI
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_INPUT);	// MISO
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_OUTPUT);	// CK
	_delay_ms(200);
	SPI_voidInit();
	_delay_ms(200);


	TIM0_voidInit();
//	/* 8 Ms/ 8 >> 1M HZ >> tick time = 1/ 1M  = 1 Micro second >> overflow time = 256 * tick time = 256 micro sec  */
//	/* 1/ (256 micro sec) = 3906.25 */
//	/* ((0.25) * 256) = 64 >>> 256 - 64 = 192 */
	TIM0_voidTimerStart(TIM0_PRESCALER_8);
	sei();
	TIM0_voidOvrINTControl(TIM0_TIN_EABLE);
	TIM0_voidOvfCallback(SPICommunication);

	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT); //correct
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT); //ALARM
	LCD_voidInit();
	KPD_voidInit();

	/* password is 000 */
	u8 Local_u8APass[3] ;
	u8 Local_u8Key;
	u8 local_u8flag = 0;
	while(1){
		for(u8 i =0; i<3;){
			Local_u8Key = KPD_u8GetPressedKey();
			if( Local_u8Key != KPD_CHECK_BUTTON_PRESSED_OR_NOT ){
				Global_LCD_VIEW = '1';
				if(Local_u8Key == 'C'){
					LCD_voidSendCommand(CLEAR);
					_delay_ms(20);
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
					local_u8flag =0;
					i =0;
					continue;
				}
				Local_u8APass[i] = Local_u8Key;
				LCD_voidSetLocation(LCD_LINE1,i);
				LCD_voidSendChar(Local_u8Key);
				i++;
			}
		}
		if((Local_u8APass[0] == '0')&&(Local_u8APass[1] == '0')&&(Local_u8APass[2] == '0')){

			LCD_voidSendCommand(CLEAR);
			_delay_ms(20);
			LCD_voidSetLocation(LCD_LINE2,2);
			LCD_voidSendString("correct!");
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
			local_u8flag = 0;
			Global_SPI_Flag = 'c';
			Global_LCD_VIEW = '0';
		}
		else{
			if(local_u8flag<=2){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(20);
				LCD_voidSetLocation(LCD_LINE2,0);
				LCD_voidSendString("please try again!");
				Global_SPI_Flag = 'p';
				local_u8flag ++;
			}
		}
		if(local_u8flag == 3){
			LCD_voidSendCommand(CLEAR);
			_delay_ms(20);
			LCD_voidSetLocation(LCD_LINE2,2);
			LCD_voidSendString("wrong!");
			Global_SPI_Flag = 'w';
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH); //ALARM ON
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW); //GREEN OFF
		}
	}
	return 0;
}



void SPICommunication(void){
	static u16 Local_u16Count =0;
	if (Local_u16Count == 4000){// 1 sec is 3906.35
		SPI_voidMasterSendData(Global_SPI_Flag);
		Local_u16Count = 0;

		u8 Local_u8Data = SPI_u8ReceiveData();
		switch(Local_u8Data){
		case'A' :
			LCD_voidSendCommand(CLEAR);
			_delay_ms(2);
			LCD_voidSetLocation(LCD_LINE1,4);
			LCD_voidSendString("Calling");
			LCD_voidSetLocation(LCD_LINE2,4);
			LCD_voidSendString("Authority!");
			DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH); //ALARM ON
			_delay_ms(750);
		break;
		case'1' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 1    off");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);//ALARM off
				_delay_ms(750);
			}
		break;
		case'2' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 2    off");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
				_delay_ms(750);
			}
		break;
		case'3' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 3    off");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
				_delay_ms(750);
			}
		break;
		case'4' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 1    on");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
				_delay_ms(750);
			}
		break;
		case'5' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 2    on");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
				_delay_ms(750);
			}
		break;
		case'6' :
			if(Global_LCD_VIEW == '0'){
				LCD_voidSendCommand(CLEAR);
				_delay_ms(2);
				LCD_voidSetLocation(LCD_LINE1,4);
				LCD_voidSendString("SPEED LIGHT");
				LCD_voidSetLocation(LCD_LINE2,4);
				LCD_voidSendString(" 3    on");
				DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
				_delay_ms(750);
			}

		break;
		default:
			//reset manually with 'C' on keypad
		break;

		}
	}
	Local_u16Count++;
}
