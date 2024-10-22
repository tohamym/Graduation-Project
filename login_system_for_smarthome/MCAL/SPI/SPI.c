/*
 * SPI.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Salem Elfaidy
 */
#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include <avr/io.h>
/*****************************************************/
#define SPI_MASTER_MODE				1
#define SPI_SLAVE_MODE				2
/*****************************************************/
#include "SPI.h"



void SPI_voidInit	(void){

#if	SPI_MODE == SPI_MASTER_MODE
	/*1- Select order ==> MSB */
	CLR_BIT(SPCR , DORD);

	/*2- select Master mode */
	SET_BIT(SPCR, MSTR);

	/*3- Clock Polarity & Phase ==> Rising_Falling ... Setup_Sample */
	CLR_BIT(SPCR , CPOL);
	SET_BIT(SPCR, CPHA);

	/*4- set clock rate fck/16 */
	SET_BIT(SPCR, SPR0);
	CLR_BIT(SPCR, SPR1);
	CLR_BIT(SPSR, SPI2X);

#elif SPI_MODE == SPI_SLAVE_MODE

	/*1- Select order ==> MSB */
	CLR_BIT(SPCR , DORD);

	/*2- select Slave mode */
	CLR_BIT(SPCR, MSTR);

	/*3- Clock Polarity & Phase ==> Rising_Falling ... Setup_Sample */
	CLR_BIT(SPCR , CPOL);
	SET_BIT(SPCR, CPHA);

#endif

	/* enable SPI */
	SET_BIT(SPCR, SPE);

}


u8   SPI_u8ReceiveData		(void){

	/* Wait for reception complete */
	while(GET_BIT(SPSR, SPIF) == 0);

	/* Return data register */
	return SPDR;

}


void SPI_voidMasterSendData (u8 Copy_u8Data){

	/* Start transmission */
	SPDR = Copy_u8Data;

	/* Wait for transmission complete */
	while(GET_BIT(SPSR, SPIF) == 0);

}


void SPI_voidSalveSendData	(u8 Copy_u8Data){

	SPDR = Copy_u8Data;

}


u8   SPI_u8ReceiveTrans		(u8 Copy_u8Data){

	/* send data */
	SPDR = Copy_u8Data;

	/* Wait for transmission complete */
	while(GET_BIT(SPSR, SPIF) == 0);

	/* Return data register */
	return SPDR;
}

