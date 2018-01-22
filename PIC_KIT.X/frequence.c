
#include "Adc.h"

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

void frequenceinit (void)
{
    mPORTBSetPinsDigitalIn(A8);
    
    T2CON = T2_ON | T2_PS_1_256 | T2_SOURCE_INT;           /*   Timer 3 SETUP */                                             
    PR2 =  1562;                                         /* SAMPLING FREQUENCY 100 Hz                                     */
    ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_7);         /* Timer 3 INTERRUPT ENABLE                                        */
    
    IFS0bits.T2IF  = 0x0000;          /* clear flag Interrup timer 2 */
    
    T4CON = T4_ON | T4_PS_1_256 | T4_SOURCE_INT;           /*   Timer 3 SETUP */                                             
    PR4 =  52083,33;                                         /* SAMPLING FREQUENCY 3 Hz                                     */
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_6);         /* Timer 3 INTERRUPT ENABLE                                        */
    
    IFS0bits.T4IF  = 0x0000;          /* clear flag Interrup timer 2 */
    count1 = 0;
    
    
   //IFS1bits.CNBIF  = 0x0000;         /* clear flag CNB ? PORTB Input Change Interrupt */
    //IEC1bits.CNBIE  = 0x0001;         /*  enable interrupt CNB ? PORTB Input Change Interrupt */
   // IPC8bits.CNIP   = 0x0006;         /* SET PRIORITY LEVEL OF INTERRUPT */
    //IPC8bits.CNIS   = 0x0000;         /* SUB PRIORITY LEVEL    */

    //Set Ports to Input/Output as specified 
   //  TRISB = 0x1000; 
   //  ANSELB = 0; // Sets all or PortB as digital
     /* STEP 1. disable interrupts */ 
   //  INTDisableInterrupts(); 
     /* STEP 2. setup the change notice options */ 
   //  mCNBOpen(CNB_ON | CNB_IDLE_CON, CNB8_ENABLE, CNB_PULLUP_DISABLE_ALL); 
     /* STEP 3. read port(s) to clear mismatch */ 
   //  int tempPortRead = mPORTBRead(); 
     /* STEP 4. set up change notice interrupt flag */ 
   //  INTEnable(INT_CNB, INT_ENABLED); 
   //  INTSetVectorPriority(INT_CHANGE_NOTICE_VECTOR, INT_PRIORITY_LEVEL_6); 
   //  INTEnable(INT_CNB, INT_ENABLED);
   //   /* STEP 5. enable multi-vector interrupts */ 
   //  INTEnableSystemMultiVectoredInt();
     
 } 
 
 /*void __ISR(_CHANGE_NOTICE_VECTOR, IPL6SOFT) _ChangeNotice_Handler(void)
 { 
     int tempPortRead = PORTB; // clear port mismatch 
     count++;
     IFS1CLR = 0x4000; //CLEAR CNB Interrupt FLAG 
     IFS0CLR = 0x0008; //CLEAR External Interrupt FLAG 
 }*/

/*void __ISR(_CHANGE_NOTICE_VECTOR, ipl6SOFT) CN_Interrupt_ISR(void)
{
   
    if (PORTBbits.RB5 == 1)
    {
     
    count++;
    }
     IFS1bits.CNBIF  = 0x0000;

}*/
void __ISR(_TIMER_2_VECTOR, ipl7SOFT) _Timer2Handler(void)
{
    if(PORTBbits.RB8 == 0)
    {
        count1++;
    }
    
    mT2ClearIntFlag();             /* CLEAR TIMER 2 INTERRUPT FLAg */
    
}

void __ISR(_TIMER_4_VECTOR, ipl6SOFT) _Timer4Handler(void)
{
   
    
    f = ((count1)*3);
    
    mT4ClearIntFlag();                                          /* CLEAR TIMER 2 INTERRUPT FLAg */
    
    count1 = 0;
    //count2 = 0;
}






