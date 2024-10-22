/*
 * SPI.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Salem Elfaidy
 */

#ifndef SPI_H
#define SPI_H

/***************************** Select Master or Slave ********************************/
#define SPI_MODE				SPI_MASTER_MODE
/* select one option: 			SPI_MASTER_MODE			SPI_SLAVE_MODE  */


/*********************************************************** APIs ************************************************************************/

void SPI_voidInit			(void);
u8   SPI_u8ReceiveData		(void);
void SPI_voidMasterSendData (u8 Copy_u8Data);
void SPI_voidSalveSendData	(u8 Copy_u8Data);
u8   SPI_u8ReceiveTrans		(u8 Copy_u8Data);


#endif /* MCAL_SPI_SPI_H_ */
