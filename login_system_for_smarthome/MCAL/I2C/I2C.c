/*
 * I2C.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Salem Elfaidy
 */
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include <avr/io.h>
#include "I2C.h"

void TWI_voidMasterInit			(void){

	/* Set prescaler value ==> 1 */
	CLR_BIT(TWSR, TWPS0);
	CLR_BIT(TWSR, TWPS1);

	/* frequency ==> 200 KHZ  >>> from the equation ==> 12 */
	TWBR = 12;

	/* Enable I2C & ACK */
	SET_BIT(TWCR, TWEA);
	SET_BIT(TWCR, TWEN);

}


void TWI_voidSlaveInit			(u8 Copy_u8Address){

	/* set slave address >> Reg address */
	TWAR = Copy_u8Address<<1;

	/* Enable I2C & ACK */
	SET_BIT(TWCR, TWEA);
	SET_BIT(TWCR, TWEN);

}


void TWI_voidStartCondition		(void){

	/* enable start bit & clear flag */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);

}


void TWI_voidStopCondition		(void){

	/* enable start bit & clear flag */
	SET_BIT(TWCR, TWSTO);
	SET_BIT(TWCR, TWINT);
}


void TWI_voidSlaveAddressWrite	(u8 Copy_u8SlaveAddress){

	TWDR = Copy_u8SlaveAddress<<1;
	CLR_BIT(TWDR, 0);

	/* disable Start condition */
	CLR_BIT(TWCR, TWSTA);

	/* clear flag */
	SET_BIT(TWCR, TWINT);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);

}


void TWI_voidSlaveAddressRead	(u8 Copy_u8SlaveAddress){

	TWDR = Copy_u8SlaveAddress<<1;
	SET_BIT(TWDR, 0);

	/* disable Start condition */
	CLR_BIT(TWCR, TWSTA);

	/* clear flag */
	SET_BIT(TWCR, TWINT);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);


}


void TWI_voidMasterSendData 	(u8 Copy_u8Data){

	TWDR = Copy_u8Data;

	/* clear flag */
	SET_BIT(TWCR, TWINT);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);

}


u8	 TWI_u8MasterReceiveData	(void){

	/* clear flag */
	SET_BIT(TWCR, TWINT);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);

	return TWDR;

}


u8	 TWI_u8SlaveReceiveData		(void){

	while((TWSR & 0xF8) != 0x60);

	/* clear flag */
	SET_BIT(TWCR, TWINT);

	/* wait flag */
	while(GET_BIT(TWCR, TWINT) == 0);

	return TWDR;

}
