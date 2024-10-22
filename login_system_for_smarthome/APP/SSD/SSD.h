/*
 * SSD.h
 *
 *  Created on: Aug 18, 2023
 *      Author: onetw
 */

#ifndef APP_SSD_H_
#define APP_SSD_H_

//#include "../../MCAL/DIO/DIO.h"


/*ports*/
#define SSD_PORT	DIO_PORTD

/*pins*/
//#define SSD_PIN_A	DIO_PIN0
//#define SSD_PIN_B	DIO_PIN1
//#define SSD_PIN_C	DIO_PIN2
//#define SSD_PIN_D	DIO_PIN3
//#define SSD_PIN_E	DIO_PIN4
//#define SSD_PIN_F	DIO_PIN5
//#define SSD_PIN_G	DIO_PIN6

/* number binary to macros */
#define ZERO		0b00111111
#define ONE			0b00000110
#define TWO			0b01011011
#define THREE		0b01001111
#define FOUR		0b01100110
#define FIVE		0b01101101
#define SIX			0b01111101
#define SEVEN		0b00000111
#define EIGHT		0b01111111
#define NINE		0b01101111
/*numbers from 0 to 9*/
#define SSD_NUMBERS	{ZERO,\
                     ONE,\
                     TWO,\
                     THREE,\
					 FOUR,\
                     FIVE,\
                     SIX,\
                     SEVEN,\
                     EIGHT,\
                     NINE}
/*******************************************/
void SSD_voidInit(void);
void SSD_voidKPDToSSD(u8 Copy_u8Char);

#endif /* APP_SSD_H_ */
