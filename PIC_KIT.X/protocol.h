/* 
 * File:   protocol.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:48
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#include <plib.h>
#include "datatypes.h"
#include "Conversion.h"
#include "Uart.h"

#define MessageLenght   10

CommandState MessageCheckFlag;
CommandState MessageConvertedFlag;




/*
 * @function CheckRxMessage
 * @brief    Check Format of Received Message
 * @param    *Data
 * @return   None
 */
void CheckRx2Message(char *Data2);

/*
 * @function ConvertTxMessage
 * @brief    Convert State Machine Message
 * @param    *Data
 * @return   None
 */
void CheckRx3Message(char *Data3);
//void ConvertTxMessage(char *Data2);

#endif	/* PROTOCOL_H */

