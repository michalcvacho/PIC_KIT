/* 
 * File:   Conversion.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:40
 */

#include "Conversion.h"
#include "Uart.h"
   

void ConvertFloatNum(float *Num, char *Buffer){
    
    int Buff[5] = {0, 0, 0, 0, 0};
    float Temp1 = 0;
    int Temp2 = 0;
    
    /* pozor na rozsah int */
    unsigned short int i;
    
    Temp1 = (*Num) * 100;
    Temp2 = (int)Temp1;
    
    if(Temp2 < 10)
    {
        Buff[0] = 0;
        Buff[1] = 0;
        Buff[2] = 0;
        Buff[3] = 0;
        Buff[4] = Temp2;
    }
    else
    {
        Buff[0] =  Temp2 * 0.0001;
        Buff[1] = (Temp2 -  (Buff[0] * 10000))*0.001;
        Buff[2] = (Temp2 - ((Buff[0] * 10000) + (Buff[1] * 1000)))*0.01;
        Buff[3] = (Temp2 - ((Buff[0] * 10000) + (Buff[1] * 1000) + (Buff[2] * 100)))*0.1;
        Buff[4] = (Temp2 - ((Buff[0] * 10000) + (Buff[1] * 1000) + (Buff[2] * 100) + (Buff[3] * 10)))*1;
    }
    
    
    for(i = 0; i < NumFloatLenght; i++)
    {
        switch(Buff[i])
        {
            case 0:   *(Buffer + (i + BufferOffSet)) = '0';   break;
            case 1:   *(Buffer + (i + BufferOffSet)) = '1';   break;
            case 2:   *(Buffer + (i + BufferOffSet)) = '2';   break;
            case 3:   *(Buffer + (i + BufferOffSet)) = '3';   break;
            case 4:   *(Buffer + (i + BufferOffSet)) = '4';   break;
            case 5:   *(Buffer + (i + BufferOffSet)) = '5';   break;
            case 6:   *(Buffer + (i + BufferOffSet)) = '6';   break;
            case 7:   *(Buffer + (i + BufferOffSet)) = '7';   break;
            case 8:   *(Buffer + (i + BufferOffSet)) = '8';   break;
            case 9:   *(Buffer + (i + BufferOffSet)) = '9';   break;
        }
    }
    
}

/*
 * @function ConvertIntNum
 * @brief    Convert num to string
 * @param    *Num, *Buffer
 * @return   None
 */
void ConvertIntNum(int *Num, char *Buffer)
{
    int Buff[4] = {0, 0, 0, 0};
    int Temp = 0;
    unsigned short int i;
    
    Temp = *Num;
    
    Buff[0] =  Temp * 0.001;
    Buff[1] = (Temp -  (Buff[0] * 1000))*0.01;
    Buff[2] = (Temp - ((Buff[0] * 1000) + (Buff[1] * 100)))*0.1;
    Buff[3] = (Temp - ((Buff[0] * 1000) + (Buff[1] * 100) + (Buff[2] * 10)));
    
    for(i = 0; i < NumIntLenght; i++)
    {
        switch(Buff[i])
        {
            case 0:    *(Buffer + (i + BufferOffSet)) = '0';    break;
            case 1:    *(Buffer + (i + BufferOffSet)) = '1';    break;
            case 2:    *(Buffer + (i + BufferOffSet)) = '2';    break;
            case 3:    *(Buffer + (i + BufferOffSet)) = '3';    break;
            case 4:    *(Buffer + (i + BufferOffSet)) = '4';    break;
            case 5:    *(Buffer + (i + BufferOffSet)) = '5';    break;
            case 6:    *(Buffer + (i + BufferOffSet)) = '6';    break;
            case 7:    *(Buffer + (i + BufferOffSet)) = '7';    break;
            case 8:    *(Buffer + (i + BufferOffSet)) = '8';    break;
            case 9:    *(Buffer + (i + BufferOffSet)) = '9';    break;
        }
    }
}