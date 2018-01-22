#include "xport.h"

/*
 * @function EthInit
 * @brief    Initialize of Ethernet XPORT
 * @param    None
 * @return   None
 */
void EthInit(void){
    
    mPORTCSetPinsDigitalIn(RX2);                                                /* SET RX2 AS DIGITAL INPUT                                              */
    mPORTCSetPinsDigitalOut(TX2);                                               /* SET TX2 AS DIGITAL INPUT                                              */

  /*mPORTBSetPinsDigitalOut(RST_ETH);*/                                         /* SET RST_ETH AS DIGITAL OUT                                            */
  /*mPORTBClearBits(RST_ETH);*/                                                 /* CLEAR RST_ETH BIT                                                     */
    
    U2RXRbits.U2RXR = 0x0006;                                                   /* PERIPHERAL PIN SELECT FOR U1RX1 RPC8                                  */
    RPC9Rbits.RPC9R = 0x0002;                                                   /* PERIPHERAL PIN SELECT FOR U1TX1 RPC9                                  */
    
    U2MODEbits.ON     = 0x0001;                                                 /* UART2 ENABLE BIT                                                      */
    U2MODEbits.IREN   = 0x0000;                                                 /* IRDA ENCODER AND DECODER ENABLE BIT                                   */
    U2MODEbits.WAKE   = 0x0000;                                                 /* ENABLE WAKE-UP ON START BIT DETECT DURING SLEEP MODE BIT              */
    U2MODEbits.LPBACK = 0x0000;                                                 /* UART2 LOOPBACK MODE SELECT BIT                                        */
    U2MODEbits.ABAUD  = 0x0000;                                                 /* AUTO-BAUD ENABLE BIT                                                  */
    U2MODEbits.PDSEL  = 0x0000;                                                 /* PARITY AND DATA SELECTION BITS                                        */
    U2MODEbits.STSEL  = 0x0000;                                                 /* STOP SELECTION BIT                                                    */
    U2MODEbits.BRGH   = 0x0001;                                                 /* HIGH BAUD RATE ENABLE BIT                                             */
    U2MODEbits.RXINV  = 0x0000;                                                 /* RECEIVE POLARITY INVERSION BIT                                        */
    U2MODEbits.UEN    = 0x0000;                                                 /* UART1 ENABLE BITS                                                     */
    
    U2STAbits.UTXEN   = 0x0001;                                                 /* TRANSMIT ENABLE BIT                                                   */
    U2STAbits.URXEN   = 0x0001;                                                 /* UART2 ENABLE BITS                                                     */
    U2STAbits.ADM_EN  = 0x0000;                                                 /* AUTOMATIC ADDRESS DETECT MODE ENABLE BIT                              */
    U2STAbits.URXISEL = 0x0000;                                                 /* TX INTERRUPT MODE SELECTION BITS                                      */
    U2STAbits.OERR    = 0x0000;                                                 /* RECEIVE BUFFER OVERRUN ERROR STATUS BIT                               */
    
    U2BRG = (40000000/(BAUDrate*4))-1;                                          /* UART2 BAUD RATE REGISTER                                              */
    
    IFS1bits.U2RXIF = 0x0000;                                                   /* CLEAR UART2 INTERRUPT FLAG                                            */
    IEC1bits.U2RXIE = 0x0001;                                                   /* ENABLE INTERRUPT OF U2RX                                              */
    IPC9bits.U2IP   = 0x0001;                                                   /* SET PRIORITY LEVEL OF INTERRUPT                                       */
    IPC9bits.U2IS   = 0x0000;                                                   /* SUB PRIORITY LEVEL                                                    */
}

/*
 * @function EthTransmit
 * @brief    Send Data by Ethernet
 * @param    *Data
 * @return   None
 */
void EthTransmit(char *Data){
    
    unsigned int size = strlen(Data);
    unsigned int i = 0;
    
    while(i < size)
    {
        U2TXREG = *(Data + i);
        while(!U2STAbits.TRMT);
        i++;
    }
}

void __ISR(_UART_2_VECTOR, IPL1SOFT) _Uart2Handler(void){
    
    static unsigned int i;
    
    if(IFS1bits.U2RXIF)
    {
        if(i < EthBufferLenght)
        {
            EthBufferRx[i] = U2RXREG;
            
            if(i == (EthBufferLenght - 2))
            {
                EthCommandReceiveFlag = Received;
                i = 0;
            }
            else
            {
                EthCommandReceiveFlag = None;
                i++;
            }
        }
    }
    
    IFS1bits.U2RXIF = 0x0000;
}