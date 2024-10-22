/*
 * STPMR.h
 *
 *  Created on: Aug 18, 2023
 *      Author: Salem Elfaidy
 */

#ifndef STPMR_H_
#define STPMR_H_

/*********************************** Cfg **********************************************/

#define STP_PORT 					DIO_PORTD
/*************************************************/
#define STP_COIL_BLUE     			DIO_PIN0
#define STP_COIL_PINK     			DIO_PIN1
#define STP_COIL_YELLOW   			DIO_PIN2
#define STP_COIL_ORANGE   			DIO_PIN3
/******************************** speed ***************************************/
#define STP_SPEED_1				1
#define STP_SPEED_2				2
#define STP_SPEED_3				3
/********************************* direction************************************/
#define STP_DIRECTION_CW		1
#define STP_DIRECTION_ACW		2
#define STP_OFF					3
/***********************************APIs ************************************************/

void STP_voidInit(void);
void STP_voidRotate(u8 Copy_u8Speed, u8 Copy_u8Direction);
void Rotate(void);
void RotateCW(void);
void RotateACW(void);
void STP_voidOff(void);
void OFF(void);


#endif /* HAL_STEPPER_MOTOR_STPMR_H_ */
