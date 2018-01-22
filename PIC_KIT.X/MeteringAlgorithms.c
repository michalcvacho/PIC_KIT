/* 
 * File:   MeteringAlgorithms.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:32
 */

#include "MeteringAlgorithms.h"
#include"Uart.h"
#include "Adc.h"

/*
 * @function RMSCalc
 * @brief    Calculation of RMS value from samples
 * @param    *Samples
 * @return   None
 */


void RMS_Calc(int *Samples){
    
    float Sum   = 0;
    float Temp1 = 0;

    long Temp2   = 0;
    Result = 0;
   

    static unsigned int i;

    for(i = 0; i < (SamplesRMS); i++)
    {
        Temp1 = (*(Samples + i) - VoltageOffset) * VoltageCoef; 
        Sum += (Temp1 * Temp1);
    }

    Temp2 = ((long)Sum) >> DIVFACT;
    Result = (long)(sqrt((float)Temp2) * SCALEFACT);
    i = 0 ;

    //return(Result);
            Vector.VoltageRMS = Result;
            //BufferTx3[3] = (long)Result;
            
    int Buff[5] = {0, 0, 0, 0, 0};
    float Temp3 = 0;
    int Temp4 = 0;
   //Result = 852;
    /* pozor na rozsah int */
    unsigned short int j;
    
    Temp3 = (Result) * 100;
    Temp4 = (int)Temp3;
    
    if(Temp4 < 10)
    {
        Buff[0] = 0;
        Buff[1] = 0;
        Buff[2] = 0;
        Buff[3] = 0;
        Buff[4] = Temp4;
    }
    else
    {
        Buff[0] =  Temp4 * 0.00001;
        Buff[1] = (Temp4 -  (Buff[0] * 100000))*0.0001;
        Buff[2] = (Temp4 - ((Buff[0] * 100000) + (Buff[1] * 10000)))*0.001;
        Buff[3] = (Temp4 - ((Buff[0] * 100000) + (Buff[1] * 10000) + (Buff[2] * 1000)))*0.01;
        Buff[4] = (Temp4 - ((Buff[0] * 100000) + (Buff[1] * 10000) + (Buff[2] * 1000) + (Buff[3] * 100)))*0.1;
    }
    
    
    for(j = 0; j < NumFloatLenght; j++)
    {
        switch(Buff[j])
        {
            case 0:   BufferTx3[j + BufferOffSet] = '0';   break;
            case 1:   BufferTx3[j + BufferOffSet] = '1';   break;
            case 2:   BufferTx3[j + BufferOffSet] = '2';   break;
            case 3:   BufferTx3[j + BufferOffSet] = '3';   break;
            case 4:   BufferTx3[j + BufferOffSet] = '4';   break;
            case 5:   BufferTx3[j + BufferOffSet] = '5';   break;
            case 6:   BufferTx3[j + BufferOffSet] = '6';   break;
            case 7:   BufferTx3[j + BufferOffSet] = '7';   break;
            case 8:   BufferTx3[j + BufferOffSet] = '8';   break;
            case 9:   BufferTx3[j + BufferOffSet] = '9';   break;
           
     }
        
    }
    int Buffreq[2] = {0, 0};
    float Temp5 = 0;
    int Temp6 = 0;
    
    /* pozor na rozsah int */
    unsigned short int k;
    
    Temp5 = (f) * 10;
    Temp6 = (int)Temp5;
    
    BufferTx3[0]='U';
    BufferTx3[1]='A';
    BufferTx3[2]='=';
    BufferTx3[7]='f';
    
    if(Temp6 < 10)
    {
        
        Buffreq[0] = 0;
        Buffreq[1] = Temp6;
    }
    else
    {
        Buffreq[0] =  Temp6 * 0.01;
        Buffreq[1] = (Temp6 -  (Buffreq[0] * 100))*0.1;
        
    }
    
    
    for(k = 0; k < 2; k++)
    {
        switch(Buffreq[k])
            {
            case 0:   BufferTx3[k + BufferOffsetFreq] = '0';   break;
            case 1:   BufferTx3[k + BufferOffsetFreq] = '1';   break;
            case 2:   BufferTx3[k + BufferOffsetFreq] = '2';   break;
            case 3:   BufferTx3[k + BufferOffsetFreq] = '3';   break;
            case 4:   BufferTx3[k + BufferOffsetFreq] = '4';   break;
            case 5:   BufferTx3[k + BufferOffsetFreq] = '5';   break;
            case 6:   BufferTx3[k + BufferOffsetFreq] = '6';   break;
            case 7:   BufferTx3[k + BufferOffsetFreq] = '7';   break;
            case 8:   BufferTx3[k + BufferOffsetFreq] = '8';   break;
            case 9:   BufferTx3[k + BufferOffsetFreq] = '9';   break;
           
            }
    
        }
    
}
       
    


/*
 * @function MAX_Calc
 * @brief    Calculation of Maximum voltage value
 * @param    None
 * @return   None
 */
void MAX_Calc(void){
    
    float Temp = 0;

    Temp = (float)(Vector.VoltageRMS) * SQRT2;
    Vector.VoltageMAX = (int)Temp;
    
}

/*
 * @function AVG_Calc
 * @brief    Calculation of Average voltage value
 * @param    None
 * @return   None
 */
void AVG_Calc(void){
    
    float Temp = 0;

    Temp = (float)Vector.VoltageMAX * VoltageAvgCoef;
    Vector.VoltageAVG = (int)Temp;
    
}
