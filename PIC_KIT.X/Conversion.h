/* 
 * File:   Conversion.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:45
 */
#ifndef CONVERSION_H
#define	CONVERSION_H

#include <plib.h>
#include <string.h>
#include "datatypes.h"
#include "protocol.h"
#include "Uart.h"


#define NumFloatLenght       5
#define NumIntLenght         5
#define BufferOffSet         3
#define BufferOffsetFreq     8


/*
 * @function ConvertFloatNum
 * @brief    Convert num to string
 * @param    *Num, *Buffer
 * @return   None
 */
void ConvertFloatNum(float *Num, char *Buffer);

/*
 * @function ConvertIntNum
 * @brief    Convert num to string
 * @param    *Num, *Buffer
 * @return   None
 */
void ConvertIntNum(int *Num, char *Buffer);

#endif	/* CONVERSION_H */