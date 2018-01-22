/* 
 * File:   Adc.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:46
 */


#ifndef ADC_H
#define	ADC_H

#include <plib.h>
#include "datatypes.h"

#define A9         BIT_9                                                        /* INPUT PIN RC0                                                 */
#define A10        BIT_10                                                        /* INPUT PIN UB RB10                                              */
#define A2         BIT_2                                                        /* INPUT PIN UC RB2                                            */
#define A8         BIT_8                                                        /* INPUT PIN frequency RB8                                            */

#define NumSamples 128                                                          /* DEFINE NUM OF SAMPLES IN BUFFER                               */

#if (NumSamples == 1)
    #define N_Samples 1
#elif(NumSamples == 8)
    #define N_Samples 8
#elif(NumSamples == 16)
    #define N_Samples 16
#elif(NumSamples == 32)
    #define N_Samples 32
#elif(NumSamples == 64)
    #define N_Samples 64
#elif(NumSamples == 128)
    #define N_Samples 128
#elif(NumSamples == 256)
    #define N_Samples 256
#else
    #error "The NumSamples should be 1, 8, 16, 32, 64, 128 or 256"
#endif

 int Adc9Channel1[N_Samples];                                                   /* SAMPLES BUFFER CH1                                            */
 /* int Adc1Channel2[N_Samples]; */
 /* int Adc1Channel3[N_Samples]; */
 /* int Adc1Channel4[N_Samples]; */
 /* int Adc1Channel5[N_Samples]; */
 /* int Adc1Channel6[N_Samples]; */
unsigned int count1;
unsigned int f;
unsigned int tempPortRead;

CommandState SamplesBufferState;                                          /* SAMPLES BUFFER FILL STATE FLAG                                */
CommandState BufferFillStateFlag;                                         /* BUFFER FILL STATE FLAG                                */

/*
 * @function AdcInit
 * @brief    Initialize of AD Converter
 * @param    None
 * @return   None
 */
void AdcInit(void);

#endif	/* ADC_H */

