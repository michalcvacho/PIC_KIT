/* 
 * File:   Uart.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:41
 */
#include "Uart.h"
#include"protocol.h"
  

void Uart_2Init(void){
    
    mPORTFSetPinsDigitalIn(RX2);                                                /* SET RX1 AS DIGITAL INPUT                                              */
    mPORTFSetPinsDigitalOut(TX2);                                               /* SET TX1 AS DIGITAL INPUT                                              */
    
    U2RXRbits.U2RXR = 0x0002;                                                   /* PERIPHERAL PIN SELECT FOR U2RX1 RPB2                                  */
    RPF5Rbits.RPF5R = 0x0001;                                                   /* PERIPHERAL PIN SELECT FOR U2TX1 RPB3                                  */
    
    U2MODEbits.ON     = 0x0001;                                                 /* UART1 ENABLE BIT                                                      */
    U2MODEbits.IREN   = 0x0000;                                                 /* IRDA ENCODER AND DECODER ENABLE BIT                                   */
    U2MODEbits.WAKE   = 0x0000;                                                 /* ENABLE WAKE-UP ON START BIT DETECT DURING SLEEP MODE BIT              */
    U2MODEbits.LPBACK = 0x0000;                                                 /* UART2 LOOPBACK MODE SELECT BIT                                        */
    U2MODEbits.ABAUD  = 0x0000;                                                 /* AUTO-BAUD ENABLE BIT                                                  */
    U2MODEbits.PDSEL  = 0x0000;                                                 /* PARITY AND DATA SELECTION BITS                                        */
    U2MODEbits.STSEL  = 0x0000;                                                 /* STOP SELECTION BIT                                                    */
    U2MODEbits.BRGH   = 0x0000;                                                 /* HIGH BAUD RATE ENABLE BIT                                             */
    U2MODEbits.RXINV  = 0x0000;                                                 /* RECEIVE POLARITY INVERSION BIT                                        */
    U2MODEbits.UEN    = 0x0000;                                                 /* UART2 ENABLE BITS                                                     */
    
    U2STAbits.UTXEN   = 0x0001;                                                 /* TRANSMIT ENABLE BIT                                                   */
    U2STAbits.URXEN   = 0x0001;                                                 /* UART2 ENABLE BITS                                                     */
    U2STAbits.ADM_EN  = 0x0000;                                                 /* AUTOMATIC ADDRESS DETECT MODE ENABLE BIT                              */
    U2STAbits.URXISEL = 0x0000;                                                 /* TX INTERRUPT MODE SELECTION BITS                                      */
    U2STAbits.OERR    = 0x0000;                                                 /* RECEIVE BUFFER OVERRUN ERROR STATUS BIT                               */

    U2BRG = (40000000/(BaudRate*16))-1;                                         /* UART2 BAUD RATE REGISTER                                              */

    
    IFS1bits.U2RXIF = 0x0000;                                                   /* CLEAR UART2 INTERRUPT FLAG                                            */
    IEC1bits.U2RXIE = 0x0001;                                                   /* ENABLE INTERRUPT OF U2RX                                              */
    IPC9bits.U2IP   = 0x0002;                                                   /* SET PRIORITY LEVEL OF INTERRUPT                                       */
    IPC9bits.U2IS   = 0x0000;                                                   /* SUB PRIORITY LEVEL                                                    */
    
}

void Uart_3Init(void)
{
    
    mPORTGSetPinsDigitalIn(RX3);                                                /* SET RX3 AS DIGITAL INPUT                                              */
    mPORTGSetPinsDigitalOut(TX3);                                               /* SET TX3 AS DIGITAL INPUT                                              */
    
    U3RXRbits.U3RXR = 0x0001;                                                   /* PERIPHERAL PIN SELECT FOR U3RX3 RPG7                                  */
    RPG8Rbits.RPG8R = 0x0001;                                                   /* PERIPHERAL PIN SELECT FOR U3TX3 RPG8                                 */
    
    U3MODEbits.ON     = 0x0001;                                                 /* UART3 ENABLE BIT                                                      */
    U3MODEbits.IREN   = 0x0000;                                                 /* IRDA ENCODER AND DECODER ENABLE BIT                                   */
    U3MODEbits.WAKE   = 0x0000;                                                 /* ENABLE WAKE-UP ON START BIT DETECT DURING SLEEP MODE BIT              */
    U3MODEbits.LPBACK = 0x0000;                                                 /* UART3 LOOPBACK MODE SELECT BIT                                        */
    U3MODEbits.ABAUD  = 0x0000;                                                 /* AUTO-BAUD ENABLE BIT                                                  */
    U3MODEbits.PDSEL  = 0x0000;                                                 /* PARITY AND DATA SELECTION BITS                                        */
    U3MODEbits.STSEL  = 0x0000;                                                 /* STOP SELECTION BIT                                                    */
    U3MODEbits.BRGH   = 0x0000;                                                 /* HIGH BAUD RATE ENABLE BIT                                             */
    U3MODEbits.RXINV  = 0x0000;                                                 /* RECEIVE POLARITY INVERSION BIT                                        */
    U3MODEbits.UEN    = 0x0000;                                                 /* UART2 ENABLE BITS                                                     */
    
    U3STAbits.UTXEN   = 0x0001;                                                 /* TRANSMIT ENABLE BIT                                                   */
    U3STAbits.URXEN   = 0x0001;                                                 /* UART2 ENABLE BITS                                                     */
    U3STAbits.ADM_EN  = 0x0000;                                                 /* AUTOMATIC ADDRESS DETECT MODE ENABLE BIT                              */
    U3STAbits.URXISEL = 0x0000;                                                 /* TX INTERRUPT MODE SELECTION BITS                                      */
    U3STAbits.OERR    = 0x0000;                                                 /* RECEIVE BUFFER OVERRUN ERROR STATUS BIT                               */

    U3BRG = (40000000/(BaudRate*16))-1;                                         /* UART3 BAUD RATE REGISTER                                              */

    
    IFS1bits.U3RXIF = 0x0000;                                                   /* CLEAR UART3 INTERRUPT FLAG                                            */
    IEC1bits.U3RXIE = 0x0001;                                                   /* ENABLE INTERRUPT OF U2RX                                              */
    IPC9bits.U3IP   = 0x0003;                                                   /* SET PRIORITY LEVEL OF INTERRUPT                                       */
    IPC9bits.U3IS   = 0x0000;                                                   /* SUB PRIORITY LEVEL                                                    */
    
}



void Uart_2Transmit(char *Data4)
{
    
    unsigned int size = strlen(Data4);
    unsigned int i = 0;
    
    while(i < size)
    {
        U2TXREG = *(Data4 + i);
        while(!U2STAbits.TRMT);
        i++;
    }
    
}

void __ISR(_UART_2_VECTOR, IPL2SOFT) _Uart2Handler(void){
    
   static unsigned int i;
   
    
    if(IFS1bits.U2RXIF)
    {   
        if(i < BufferLenght)
        {      
            BufferRx2[i] = U2RXREG;
            
            if((BufferRx2[i] == '\n')||(i == (BufferLenght - 1)))
                
            
            //if(i == (BufferLenght - 1))
            {
                CommandReceiveFlagUART_2 = Received;
                i = 0;
            }
            else 
            {
               CommandReceiveFlagUART_2 = None;
                i++;
            }
        }
    }
    IFS1bits.U2RXIF = 0x0000; 
}

void Uart_3Transmit(char *Data5){
    
    unsigned int size = strlen(Data5);
    unsigned int i = 0;
    
    while(i < size)
    {
        U3TXREG = *(Data5 + i);
        while(!U3STAbits.TRMT);
        i++;
    }
    
}
void __ISR(_UART_3_VECTOR, IPL3SOFT) _Uart3Handler(void){
    
   static unsigned int i;
    
    if(IFS1bits.U3RXIF)
    {   
        if(i < BufferLenght)
        {      
            BufferRx3[i] = U3RXREG;
            
            if((BufferRx3[i] == '\n')||(i == (BufferLenght - 1)))
            {
                CommandReceiveFlagUART_3 = Received;
                i = 0;
            }
            else
            {
                CommandReceiveFlagUART_3 = None;
                i++;
            }
        }
    }
    IFS1bits.U3RXIF = 0x0000; 
}
