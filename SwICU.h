/*
 * SwICU.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Sprints
 */

#ifndef SWICU_H_
#define SWICU_H_

#include "interrupt.h"
#include "timers.h"

typedef enum EN_SwICU_Edge_t{
	SwICU_EdgeFalling = 2,
	SwICU_EdgeRisiging = 3
}EN_SwICU_Edge_t;

/**
 * Description: Initializing the software ICU module
 * @param a_en_inputCaptureEdge: The external interrupt sense to be used first
 *              and takes the following values:
 * 				- 2 -> SwICU_EdgeFalling
 * 				- 3 -> SwICU_EdgeRisiging
 */
void SwICU_Init(EN_SwICU_Edge_t a_en_inputCaptureEdge);


//EN_SwICU_Edge_t SwICU_GetCfgEdge(void);

/**
 * Description: resets the sense of the external interrupt 
 * @param a_en_inputCaptureEdgeedge: The external interrupt sense to be used
 *              and takes the following values:
 * 				- 2 -> SwICU_EdgeFalling
 * 				- 3 -> SwICU_EdgeRisiging
 */
void SwICU_SetCfgEdge(EN_SwICU_Edge_t a_en_inputCaptureEdgeedge);

/**
 * Description: reads the value of TCNT0 (Timer/Counter 0 Register)
 * @param a_pu8_capt: takes the addres of the variable that the value
 *					of TCNT0 will be stored in
 */
void SwICU_Read(volatile uint8_t* a_pu8_capt);

/**
 * Description: Stops the software ICU module
 */
void SwICU_Stop(void);

/**
 * Description: Starts the software ICU module
 */
void SwICU_Start(void);


//void SwICU_Enable(void);
//void SwICU_Disable(void);

#endif /* SWICU_H_ */
