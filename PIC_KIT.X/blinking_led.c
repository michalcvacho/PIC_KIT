

#define SYSCLK 16000000L // Give the system?s clock frequency
 
#include <p32xxxx.h> // Include PIC32 specifics header file
#include <plib.h> // Include the PIC32 Peripheral Library
//#include <xc.h>
//
//#pragma config POSCMOD = HS
//#pragma config FNOSC = PRIPLL       
//#pragma config FCKSM = CSECME
//#pragma config FPLLIDIV = DIV_3
//#pragma config FPLLMUL = MUL_20
//#pragma config FPLLODIV = DIV_2
//

#include <xc.h>
#pragma config POSCMOD = HS
#pragma config FNOSC = SPLL
#pragma config FPLLICLK = PLL_POSC
#pragma config FPLLIDIV = DIV_3
#pragma config FPLLRNG = RANGE_5_10_MHZ
#pragma config FPLLMULT = MUL_50
#pragma config FPLLODIV = DIV_2
#define SYSFREQ (200000000L)
int cnt = 0;

int main(void){
 
        SYSTEMConfigPerformance(SYSCLK);
 
          // Sets RD8 and RD9 as digital outputs
 
        OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_256, 0xFFFF);
        // This statement says: turn on timer2 | have it use an internal clock source | have it
        // use a prescaler of 1:256, and use a period of 0xFFFF or 2^16 cycles
 
        // Timer2 as configured would trigger an interrupt at a frequency of (80MHZ/256/65535), or 4.77
        // times a second.
 
        ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2);
        // This statement configured the timer to produce an interrupt with a priority of 2
 
       // INTCON.MVEC = 1;
        // Use multi-vectored interrupts
            ANSELBbits.ANSB5 = 0;
            TRISBbits.TRISB5 = 0;
            PORTBbits.RB5 = 0;
          //  PORTBbits.RB5 = 1;
        while( 1)
        {
              
                // Similar to digital I/O tutorial. Pressing the PROG button will light the LED
                // that?s connected to pin RD8
        }
 
        return 1;
}
 
// Timer2 Interrupt Service Routine
void __ISR(_TIMER_2_VECTOR) T2InterruptHandler(void)
{
        // **make sure iplx matches the timer?s interrupt priority level
 
    PORTBbits.RB5 = PORTBbits.RB5^ 1;
    
              
        // This statement looks at pin RD9, and latches RD9 the inverse of the current state.
        // In other words, it toggles the LED that is attached to RD9
 
//    DMTSTAT
//        T2ClearIntFlag();
        // Clears the interrupt flag so that the program returns to the main loop
} // END Timer2 ISR