/* 
 * File:   Uart.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:44
 */

#ifndef _UARTLBR_H
#define	_UARTLBR_H

#include <plib.h>
#include <string.h>
#include "datatypes.h"
#include "protocol.h"
#include "Conversion.h"


#define RX2            BIT_4                                                    /* U2RX2 PIN                                    */
#define TX2            BIT_5                                                    /* U2TX2 PIN                                    */

#define RX3            BIT_7                                                   /* U3RX3 PIN                                    */
#define TX3            BIT_8                                                    /* U3TX3 PIN                                    */

#define BaudRate       250000                                                   /* BAUDRATE 250 000 Baud                        */
#define BufferLenght   10                                                       /* BUFFERS LENGHT                                */
#define BufferLenghtTx3   15                                                       /* BUFFERS LENGHT Tx3                               */

CommandState CommandReceiveFlagUART_2;                                                /* COMMAND RECEIVE FLAG            for UART_2             */
CommandState CommandReceiveFlagUART_3;                                                /* COMMAND RECEIVE FLAG            for UART_3           */
CommandState CommandReceiveFlag;                                                    /* COMMAND RECEIVE FLAG            for UART_2             */

char BufferTx2[BufferLenght];                                                    /* TX2 BUFFER                                    */
char BufferRx2[BufferLenght];                                                    /* RX2 BUFFER                                    */
char BufferTx3[BufferLenghtTx3] ;                                                   /* TX2 BUFFER                                    */
char BufferRx3[BufferLenght];                                                    /* RX2 BUFFER                                    */


/*
 * @function UartInit
 * @brief    Initialize of UART
 * @param    None
 * @return   None
 */
void Uart_2Init(void);

/*
 * @function UartTransmit
 * @brief    Send Data by Uart
 * @param    *Data
 * @return   None
 */
void Uart_2Transmit(char *Data4);
/*
 * @function UartInit
 * @brief    Initialize of UART
 * @param    None
 * @return   None
 */

void Uart_3Init(void);

/*
 * @function UartTransmit
 * @brief    Send Data by Uart
 * @param    *Data
 * @return   None
 */
void Uart_3Transmit(char *Data5);
/*
 * @function UartInit
 * @brief    Initialize of UART
 * @param    None
 * @return   None
 */




#endif	/* _UARTH */

