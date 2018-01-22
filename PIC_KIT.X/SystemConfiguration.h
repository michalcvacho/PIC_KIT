/* 
 * File:   SystemConfiguration.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:50
 */

#ifndef _SYSTEMCONFIGURATION_H
#define	_SYSTEMCONFIGURATION_H

#pragma config FNOSC    =   FRCPLL          /* INTERNAL FAST RC OSC WITH PLL          */
#pragma config FPLLIDIV =   DIV_2           /* PLL INPUT DIVIDER 2x                   */
#pragma config FPLLMUL  =   MUL_20          /* PLL MULTIPLIER 20x                     */
#pragma config FPLLODIV =   DIV_2           /* SYSTEM PLL OUTPUT CLOCK DIVIDER 2x     */
#pragma config FPBDIV   =   DIV_1           /* PERIPHERAL CLOCK DIVIDER               */
#pragma config POSCMOD  =   OFF             /* PRIMARY OSC DISABLED                   */
#pragma config FSOSCEN  =   OFF             /* SECONDARY OSCILLATOR DISABLED          */
#pragma config ICESEL   =   ICS_PGx1        /* COMMUNICATE ON PGEC1/PGED1             */
#pragma FWDTEN          =   OFF             /* WATCHDOG TIMER DISABLED                */
#pragma JTAGEN          =   OFF             /* JTAG PORT DISABLED                     */

#define SYS_FREQ            (40000000L)     /* SYSTEM FREQUENCY                       */

#endif	/* _SYSTEMCONFIGURATION_H */

