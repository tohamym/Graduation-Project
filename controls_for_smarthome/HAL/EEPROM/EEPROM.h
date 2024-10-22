/*
 * EEPROM.h
 *
 *  Created on: Aug 27, 2023
 *      Author: hosni
 */

#ifndef EEPROM_H_
#define EEPROM_H_

/********************Select EEPROM A2 PIN HIGH or LOW***************************/
#define A2		0
/*  Options:    0     <or> 		1  */

/************************************************* APIs *********************************************/

void EEPROM_VidWriteDataByte(u16 Copy_u16ByteAddress,u8 Copy_u8Data);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress);


#endif /* EEPROM_H_ */
