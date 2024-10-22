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

/***********************************APIs ************************************************/

void STP_voidInit(void);
void STP_voidRotateCW(void);
void STP_voidRotateACW(void);


#endif /* HAL_STEPPER_MOTOR_STPMR_H_ */
