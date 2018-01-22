/* 
 * File:   main.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:23
 */
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>
#include "SystemConfiguration.h"
#include "Uart.h"
#include "protocol.h"
#include "Adc.h"
#include "Conversion.h"
#include "datatypes.h"
#include "MeteringAlgorithms.h"

int main(void){
 
    

    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    
    T1CONbits.ON = 0x0001;
    T1CONbits.TCKPS = 0x0003;
    T1CONbits.TCS = 0x0000;
    PR1 = 0xFFFF;
    IEC0bits.T1IE = 0x0001;
    IPC1bits.T1IP = 0x0001;
    IPC1bits.T1IS = 0x0000;
    
   
    Uart_2Init();
    INTEnableSystemMultiVectoredInt(); 
    Uart_3Init();
    INTEnableSystemMultiVectoredInt(); 
    
    
    AdcInit();
    INTEnableSystemMultiVectoredInt(); 
 
    frequenceinit();
    INTEnableSystemMultiVectoredInt(); 
  
   
    while(1)
    {
      
     //}
         if(BufferFillStateFlag == Full)
             
         {
      
                RMS_Calc(&Adc9Channel1);
                
                
         }
       //  else if(CommandReceiveFlagUART_2 == Received)
     //  {
            
           // CheckRx2Message(&BufferRx2);
            //CommandReceiveFlagUART_2 = None;
          
     //  }
     else if (CommandReceiveFlagUART_3 == Received);
       
       {
          CheckRx3Message(&BufferRx3);
          CommandReceiveFlagUART_3 = None;
     //}
        
         }
 
 
    
    }
   }
  

 void __ISR(_TIMER_1_VECTOR, ipl1SOFT) _Timer1Handler(void)
{
    
      Uart_2Transmit(&BufferTx2);
      Uart_3Transmit(&BufferTx3);
        
    mT1ClearIntFlag();
}


 
 
 

  