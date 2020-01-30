/*
 * timers.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Sprints
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "registers.h"
#include "gpio.h"

/*
 * User Configuration Macros
 */

#define T0_PWM_GPIO	GPIOD
#define T0_PWM_BIT	BIT0

#define T1_PWM_GPIO	GPIOD
#define T1_PWM_BIT	BIT1

#define T2_PWM_GPIO GPIOD
#define T2_PWM_BIT	BIT2


#define TOV0   ((TIFR>>0)&0x01)
#define SYNC	0x08
#define ASSYNC	0x00
#define T0_STOP TCCR0>>=3;\
				TCCR0<<=3
				
#define T1_STOP TCCR1>>=3;\
				TCCR1<<=3

#define T2_STOP TCCR2>>=3;\
				TCCR2<<=3





/************************************************************************/
/*				 Enum for defining frequancies                          */
/************************************************************************/
typedef enum En_frequancy_t{
	F_8000,			/* 8000 Hz frequancy*/
	F_2000,			/* 2000 Hz frequancy*/
	F_1000,			/* 1000 Hz frequancy*/
	F_500,			/* 500 Hz frequancy*/
	F_250,			/* 250 Hz frequancy*/
	F_60			/* 60 Hz frequancy*/
}En_frequancy_t;

//For Timer0

/************************************************************************/
/*				 Enum for defining timer0 modes                         */
/************************************************************************/
typedef enum En_timer0Mode_t{
	T0_NORMAL_MODE=0,			/* timer0 normal mode*/
	T0_COMP_MODE=0x08			/* timer0 CTC (Clear time at compare match) mode */
}En_timer0Mode_t;

/********************************************************************************************/
/*				 Enum for defining timer0 OC (output compare) modes                         */
/********************************************************************************************/
typedef enum En_timer0OC_t{
	T0_OC0_DIS=0,		/* OC0 disable */
	T0_OC0_TOGGLE=0x10, /* OC0 Toggle at compare match */
	T0_OC0_CLEAR=0x20,	/* OC0 Clear at compare match */
	T0_OC0_SET=0x30		/* OC0 Set at compare match */
}En_timer0OC_t;

/************************************************************************/
/*				 Enum for defining timer0 prescalers                    */
/************************************************************************/
typedef enum En_timer0perscaler_t{
	T0_NO_CLOCK=0,			/* Disable the clock source on Timer0 */
	T0_PRESCALER_NO=0x01,	/* Timer0 no prescaler */
	T0_PRESCALER_8=0x02,	/* Timer0 prescaler 8 */
	T0_PRESCALER_64=0x03,	/* Timer0 prescaler 64 */
	T0_PRESCALER_256=0x04,	/* Timer0 prescaler 256 */
	T0_PRESCALER_1024=0x05	/* Timer0 prescaler 1024 */
}En_timer0perscaler_t;

/************************************************************************/
/*				 Enum for defining timer0 interrupts                    */
/************************************************************************/
typedef enum En_timer0Interrupt_t{
	T0_POLLING=0,				/* Timer0 Polling (no interrupts) */
	T0_INTERRUPT_NORMAL=0x01,	/* Timer0 overflow interrupt enable */
	T0_INTERRUPT_CMP=0x02 ,		/* Timer0 compare match interrupt enable */
	T0_ALL_INTERRUPT=0x03		/* Timer0 enable all interrupts */
}En_timer0Interrupt_t;


/***************************************************************************************************************/
/*                             Timer1 is not implemented yet                                                   */
/***************************************************************************************************************/

// For Timer1
typedef enum En_timer1Mode_t{
	T1_NORMAL_MODE=0x0000,T1_COMP_MODE_OCR1A_TOP=0x0008, T1_COMP_MODE_ICR1_TOP = 0x0018

}En_timer1Mode_t;
typedef enum En_timer1OC_t{
	T1_OC1_DIS=0,
	T1_OC1A_TOGGLE=0x4000,
	T1_OC1B_TOGGLE=0x1000,
	T1_OC1A_CLEAR=0x8000,
	T1_OC1B_CLEAR=0x2000,
	T1_OC1A_SET=0xC000,
	T1_OC1B_SET=0x3000
}En_timer1OC_t;

typedef enum En_timer1perscaler_t{
	T1_NO_CLOCK=0x0000,
	T1_PRESCALER_NO=0x0001,
	T1_PRESCALER_8=0x0002,
	T1_PRESCALER_64=0x0003,
	T1_PRESCALER_256=0x0004,
	T1_PRESCALER_1024=0x0005
}En_timer1perscaler_t;

typedef enum En_timer1Interrupt_t{
	T1_POLLING=0,
	T1_INTERRUPT_NORMAL=0x04,
	T0_INTERRUPT_CMP_1B=0x08,
	T1_INTERRUPT_CMP_1A=0x10,
	T1_INTERRUPT_ICAPTURE = 0x20
}En_timer1Interrupt_t;



//For Timer2

/************************************************************************/
/*				 Enum for defining timer2 modes                         */
/************************************************************************/
typedef enum En_timer2Mode_t{
	T2_NORMAL_MODE=0,		/* Timer2 Normal mode */
	T2_COMP_MODE=0x08		/* Timer2 CTC (Clear time at compare match) mode */
}En_timer2Mode_t;

/********************************************************************************************/
/*				 Enum for defining timer2 OC (Output Compare) modes                         */
/********************************************************************************************/
typedef enum En_timer2OC_t{
	T2_OC2_DIS=0,		/* Timer2 OC disable */
	T2_OC2_TOGGLE=0x10,	/* Timer2 toggle at compare match */
	T2_OC2_CLEAR=0x20,	/* Timer2 clear at compare match */
	T2_OC2_SET=0x30		/* Timer2 set at compare match */
}En_timer2OC_t;

/****************************************************************************/
/*				 Enum for defining timer2 prescalers                        */
/****************************************************************************/
typedef enum En_timer2perscaler_t{
	T2_NO_CLOCK=0,				/* Disable clock source on Timer2 */
	T2_PRESCALER_NO=0x01,		/* Timer2 no prescaler */
	T2_PRESCALER_8=0x02,		/* Timer2 prescaler 8 */ 
	T2_PRESCALER_32=0x03,		/* Timer2 prescaler 32 */ 
	T2_PRESCALER_64=0x04,		/* Timer2 prescaler 64 */
	T2_PRESCALER_128=0x05,		/* Timer2 prescaler 128 */
    T2_PRESCALER_256 = 0x06,	/* Timer2 prescaler 256 */ 
	T2_PRESCALER_1024=0x07		/* Timer2 prescaler 1024 */
}En_timer2perscaler_t;

/*******************************************************************************/
/*				 Enum for defining timer2 interrupts                           */
/*******************************************************************************/
typedef enum En_timer2Interrupt_t{
	T2_POLLING=0,					/* Timer2 Polling (no interrupts) */
	T2_INTERRUPT_NORMAL=0x40,		/* Timer2 overflow interrupt enable */
	T2_INTERRUPT_CMP=0x80,			/* Timer2 compare match interrupt enable */
	T2_ALL_INTERRUPT=(0X40|0X80)	/* Enable all Timer2 interrupts */
}En_timer2Interrupt_t;







/*===========================Timer0 Control===============================*/
/**
 * Description: Timer0 initialize function
 * @param en_mode takes the following values:
 * 0    -> T0_Normal_Mode
 * 0x08 -> T0_COMP_Mode
 * @param en_OC0 takes the following values:
 * 0    -> T0_OC0_DIS
 * 0x10 -> T0_OC0_TOGGLE
 * 0x20 -> T0_OC0_CLEAR
 * 0x30 -> T0_OC0_SET
 * @param en_prescal takes the following values:
 * 0    -> T0_PRESCALER_NO
 * 0x01 -> T0_PRESCALER_8
 * 0x02 -> T0_PRESCALER_64
 * 0x03 -> T0_PRESCALER_256
 * 0x04 -> T0_PRESCALER_1024
 * @param u8_initialValue takes values from 0~255
 * @param u8_outputCompare takes values from 0~255
 * @param en_interruptMask takes the following values:
 * 0    -> T0_POLLING
 * 0x01 -> T0_INTERRUPT_NORMAL
 * 0x02 -> T0_INTERRUPT_CMP
 * 0x03 -> T0_ALL_INTERRUPT
 */
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t  en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask);

/**
 * Description: Sets the argument value to TCNT0 (Timer/Counter 0 Register)
 * @param u8_value takes values from 0~255
 */
void timer0Set(uint8_t u8_value);

/**
 * Description: Reads the value of the TCNT0 (Timer/Counter 0 Register)
 * @return TCNT0 expected to be a value from 0~255
 */
uint8_t timer0Read(void);

/**
 * Description: Starts Timer0 by giving the timer/counter register a clock source
 */
void timer0Start(void);

/**
 * Description: stops Timer0 by removing the clock source on timer/counter register
 */
void timer0Stop(void);

/**
 * Description: function to make a delay by stucking in it for a period of time
 * @param u16_delay_in_ms takes any values as a notation for the required time to be delayed in ms
 */
void timer0DelayMs(uint16_t u16_delay_in_ms);

/**
 * Description: function to make a delay by stucking in it for a period of time
 * @param u16_delay_in_us takes any values as a notation for the required time to be delayed in us
 */
void timer0DelayUs(uint32_t u32_delay_in_us);

/**
 * Description: a function to generate a software PWM signal using timer0
 * @param u8_dutyCycle takes values from 0~255
 * @param u8_frequancy takes values from the enum  "En_frequancy_t":
 * 0    -> F_8000
 * 0x02 -> F_1000
 * 0x04 -> F_250
 * 0x05 -> F_60
 */
void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);




/*===========================Timer1 Control===============================*/ /*NOT IMPLEMENTED YET*/

/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */

void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask);

/**
 * Description:
 * @param value
 */

void timer1Set(uint16_t u16_value);

/**
 * Description:
 * @return
 */

uint16_t timer1Read(void);

/**
 * Description:
 */

void timer1Start(void);

/**
 * Description:
 */

void timer1Stop(void);

/**
 * Description:
 * @param delay
 */

void timer1DelayMs(uint16_t u16_delay_in_ms);

/*
 * user defined
 */

void timer1DelayUs(uint32_t u32_delay_in_us);

/**
 * Description:
 * @param dutyCycle
 */

void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);

/*===========================Timer2 Control===============================*/
/**
 * Description: Timer2 initialize function
 * @param en_mode takes the following values:
 * 0    -> T2_Normal_Mode
 * 0x08 -> T2_COMP_Mode
 * @param en_OC2 takes the following values:
 * 0    -> T2_OC2_DIS
 * 0x10 -> T2_OC2_TOGGLE
 * 0x20 -> T2_OC2_CLEAR
 * 0x30 -> T2_OC2_SET
 * @param en_prescal takes the following values:
 * 0    -> T2_PRESCALER_NO
 * 0x01 -> T2_PRESCALER_8
 * 0x02 -> T2_PRESCALER_32
 * 0x03 -> T2_PRESCALER_64
 * 0x04 -> T2_PRESCALER_128
 * 0X05 -> T2_PRESCALER_256
 * 0x06 -> T2_PRESCALER_1024
 * @param u8_initialValue takes values from 0~255
 * @param u8_outputCompare takes values from 0~255
 * @param u8_outputCompare takes values from 0 or 1
 * @param en_interruptMask takes the following values:
 * 0    -> T0_POLLING
 * 0x01 -> T0_INTERRUPT_NORMAL
 * 0x02 -> T0_INTERRUPT_CMP
 * 0x03 -> T0_ALL_INTERRUPT
 */
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask);
/**
 * Description: Sets TCNT2 (Timer/Counter 2 register) by a value 
 * @param u8_a_value takes values from 0~255
 */
void timer2Set(uint8_t u8_a_value);

/**
 * Description: Reads the value of TCNT2 (Timer/Counter 2 register)
 * @return TCNT2 expected to be a value from 0~255
 */
uint8_t timer2Read(void);

/**
 * Description: Starts timer2 by providing a clock source to TCNT2 (Timer/Counter 2 register)
 */
void timer2Start(void);

/**
 * Description: Stops timer2 by removing the clock source from TCNT2 (Timer/Counter 2 register)
 */
void timer2Stop(void);

/**
 * Description: function to make a delay by stucking in it for a period of time
 * @param u16_delay_in_ms takes any values as a notation for the required time to be delayed in ms
 */
void timer2DelayMs(uint16_t u16_delay_in_ms);

/**
 * Description: function to make a delay by stucking in it for a period of time
 * @param u16_delay_in_us takes any values as a notation for the required time to be delayed in us
 */
void timer2DelayUs(uint32_t u16_delay_in_us);

/**
 * Description: a function to generate a software PWM signal using timer2
 * @param u8_dutyCycle takes values from 0~255
 * @param u8_frequancy takes values from the enum  "En_frequancy_t":
 * 0    -> F_8000
 * 0x01 -> F_2000
 * 0x02 -> F_1000
 * 0x03 -> F_500
 * 0x04 -> F_250
 * 0x05 -> F_60
 */
void timer2SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency);

#endif /* TIMERS_H_ */