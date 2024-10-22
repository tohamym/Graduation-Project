#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"
#include "../../MCAL/I2C/I2C.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "EEPROM.h"

/************************************************/
#define uniquAdderess		0x50		// 0b01010000
/***********************************************/


void EEPROM_VidWriteDataByte(u16 Copy_u16ByteAddress, u8 Copy_u8Data) // 0b01010011
{
	/* Start condition */
	TWI_voidStartCondition();

	/* Send Byte Address with write operation */
	TWI_voidSlaveAddressWrite(uniquAdderess|(A2<<2)|(Copy_u16ByteAddress>>8));

	/*Send rest of address*/
	TWI_voidMasterSendData((u8)Copy_u16ByteAddress);

	/*Send Data*/
	TWI_voidMasterSendData(Copy_u8Data);

	/* stop condition */
	TWI_voidStopCondition();

	/* delay 5 ms for rewrite */
	_delay_ms(10);
}



u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress)
{
	u8 Local_u8data;
	/* Start condition */
	TWI_voidStartCondition();

	/*Send Byte Address with Write operation*/
	TWI_voidSlaveAddressWrite((uniquAdderess)|(A2<<2)|(Copy_u16ByteAddress>>8));

	/*Send rest of address*/
	TWI_voidMasterSendData((u8)Copy_u16ByteAddress);

	/*Send Repeat start condition*/
	TWI_voidStartCondition();

	/*Send Byte Address with Read operation*/
	TWI_voidSlaveAddressRead((uniquAdderess)|(A2<<2)|(Copy_u16ByteAddress>>8));

	Local_u8data = TWI_u8MasterReceiveData();

	/* stop condition */
	TWI_voidStopCondition();

	return Local_u8data;

}













