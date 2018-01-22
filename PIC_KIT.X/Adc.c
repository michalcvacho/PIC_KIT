/* 
 * File:   Adc.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:32
 */

#include "Adc.h"
#include <plib.h> 
unsigned int Temp;

/*
 * @function AdcInit
 * @brief    Initialize of AD Converter
 * @param    None
 * @return   None
 */
void AdcInit(void){
    
    mPORTBSetPinsAnalogIn(A9);                                                  /* SET ANALOG INPUTS  RB9/AN - UA                                                                   */
    mPORTBSetPinsAnalogIn(A10);                                                  /* SET ANALOG INPUTS  RB10/AN10 - UB               */
    mPORTBSetPinsAnalogIn(A2);                                                  /* SET ANALOG INPUTS  RB2/AN2 - UC                           */
    
    T3CON = T3_ON | T3_PS_1_1 | T3_SOURCE_INT;                                  /* Timer 3 SETUP                                                                              */
    PR3 = 6249;                                                                 /* SAMPLING FREQUENCY 6.4 kHz                                                                 */
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_4);                                /* Timer 3 INTERRUPT ENABLE                                                                   */
    
    
    AD1CON1bits.FORM    = 0x0000;                                               /* OUTPUT FORMAT INTEGER 16-bit                                                               */
    AD1CON1bits.SSRC    = 0x0002;                                               /* Timer3 PERIOD MATCH ENDS SAMPLING AND STARTS CONVERSION                                    */
    AD1CON1bits.CLRASAM = 0x0000;                                               /* NORMAL OPERATION, BUFFER CONTENTS WILL BE OVERWRITTEN BY THE NEXT CONVERSION SEQUENCE      */
    AD1CON1bits.ASAM    = 0x0001;                                               /* SAMPLING BEGINS IMMEDIATELY AFTER LAST CONVERSION COMPLETES; SAMP BIT IS AUTOMATICALLY SET */
  
    
    AD1CON2bits.VCFG    = 0x0003;                                               /* VOLTAGE REFERENCE CONFIGURATION BITS INTERNAL REFERENCE AVDD AVSS                          */
    AD1CON2bits.OFFCAL  = 0x0000;                                               /* INPUT OFFSET CALIBRATION MODE SELECT BIT                                                   */
    AD1CON2bits.CSCNA   = 0x0001;                                               /* SCAN INPUTS                                                                                */
    AD1CON2bits.SMPI    = 0x0000;                                               /* INTERRUPTS AT THE COMPLETION OF CONVERSION FOR EACH SAMPLE/CONVERT SEQUENCE                */
    AD1CON2bits.BUFM    = 0x0000;                                               /* ADC RESULT BUFFER MODE SELECT BIT                                                          */
    AD1CON2bits.ALTS    = 0x0000;                                               /* ALTERNATE INPUT SAMPLE MODE SELECT BIT                                                     */
    
    AD1CON3bits.ADRC    = 0x0000;                                               /* CLOCK DERIVED FROM PERIPHERAL BUS CLOCK (PBCLK)                                            */
    AD1CON3bits.SAMC    = 0x0012;                                               /* AUTO-SAMPLE TIME BITS                                                                      */
    AD1CON3bits.ADCS    = 0x0004;                                               /* ADC CONVERSION CLOCK SELECT BITS                                                           */
    
    AD1CHSbits.CH0NA    = 0x0000;                                               /* NEGATIVE INPUT SELECT BIT FOR MUX A MULTIPLEXER SETTINGS                                   */
    
    AD1CSSLbits.CSSL9  = 0x0001;                                               /* ADC INPUT PIN SCAN SELECTION BITS                                                          */
    //AD1CSSLbits.CSSL10 = 0x0001;                                                /* ADC INPUT PIN SCAN SELECTION BITS                                                          */
    //AD1CSSLbits.CSSL2  = 0x0001;                                                /* ADC INPUT PIN SCAN SELECTION BITS                                                          */
    
    AD1CON1bits.ON      = 0x0001;                                               /* ADC MODULE IS OPERATING                                                                    */
    
    IFS0bits.AD1IF      = 0x0000;                                               /* CLEAR ADC INTERRUPT FLAG                                                                   */
    IEC0bits.AD1IE      = 0x0001;                                               /* ENABLE INTERRUPT OF ADC MODULE                                                             */
    IPC5bits.AD1IP      = 0x0005;                                               /* SET PRIORITY LEVEL OF INTERRUPT                                                            */
    IPC5bits.AD1IS      = 0x0000;                                               /* SUB PRIORITY LEVEL                                                                         */
    
    BufferFillStateFlag = Empty;                                                /* SAMPLES BUFFER FILL STATE FLAG                                                             */
}

void __ISR(_TIMER_3_VECTOR, ipl4SOFT) _Timer3Handler(void)
{
    
    mT3ClearIntFlag();                                                          /* CLEAR TIMER 3 INTERRUPT FLAG                                                               */
}

void __ISR(_ADC_VECTOR, ipl5SOFT) _ADC1Handler(void)
{
     
    static unsigned int i;
    //unsigned int Temp;
    
    if(IFS0bits.AD1IF)
    {
        
        if(BufferFillStateFlag == Empty)
        {
            Adc9Channel1[i] = ADC1BUF0;
            
            if(i == (N_Samples - 1))
            {
                i = 0;
                BufferFillStateFlag = Full;
            }
            else
            {
                i++;
                BufferFillStateFlag = Empty;
            }
        }
        else if(BufferFillStateFlag == Full)
        {
            Temp = ADC1BUF0;
            BufferFillStateFlag = Empty;
        }
    }
    IFS0bits.AD1IF = 0x0000;                                                    /* CLEAR ADC INTERRUPT FLAG                                                                   */
}