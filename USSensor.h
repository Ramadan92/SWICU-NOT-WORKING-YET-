/*
 * USSensor.h
 *
 * Created: 1/29/2020 11:59:20 PM
 *  Author: ahmed
 */ 

#include "std_types.h"
#ifndef USSENSOR_H_
#define USSENSOR_H_

/**
 * Description: calculates the distance to be measured by the ultrasonic sensor
 * @param u8_ticks: number of ticks ticked by timer0 (TCNT0 value)
 */
uint8_t USSensor_getDistance(uint8_t u8_ticks);

/**
 * Description: sends the trigger pulse needed by the ultrasonic sensor
 * 
 */
void USSensor_Trigger(void);

#endif /* USSENSOR_H_ */