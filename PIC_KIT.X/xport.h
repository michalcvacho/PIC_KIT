/* 
 * File:   xport.h
 * Author: Michal
 *
 * Created on 18. 7. 2016, 9:32
 */

#ifndef XPORT_H
#define	XPORT_H

#include <plib.h>
#include <string.h>
#include "datatypes.h"

#define RX2             BIT_8                                                   /* U2RX2 PIN                                               */
#define TX2             BIT_9                                                   /* U2TX2 PIN                                               */
#define RST_ETH         BIT_6                                                   /* ETHERNET RESET PIN                                      */

#define BAUDrate        115200                                                  /* BAUDRATE 57600 BAUD ->U2BRG=173, 115200 BAUD ->U2BRG=86 */

#define EthBufferLenght 10                                                      /* BUFFERS LENGHT                                          */

CommandState EthCommandReceiveFlag;                                             /* ETHERNET COMMAND RECEIVE FLAG                           */
char EthBufferTx[EthBufferLenght];                                              /* ETHERNET TX BUFFER                                      */
char EthBufferRx[EthBufferLenght];                                              /* ETHERNET RX BUFFER                                      */

/*
 * @function EthInit
 * @brief    Initialize of Ethernet XPORT
 * @param    None
 * @return   None
 */
void EthInit(void);

/*
 * @function EthTransmit
 * @brief    Send Data by Ethernet
 * @param    *Data
 * @return   None
 */
void EthTransmit(char *Data);

#endif	/* XPORT_H */

