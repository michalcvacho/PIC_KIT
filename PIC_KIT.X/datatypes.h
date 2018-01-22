/* 
 * File:   datatypes.h
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:47
 */
#ifndef _DATATYPES_H
#define	_DATATYPES_H


typedef enum{
    None      = 0,
    Error     = 1,
    Received  = 2,
    Checked   = 3,
    Processed = 4,
    Converted = 5,
    Empty     = 6,
    Full      = 7,      
}CommandState;          /* DATA TYPE COMMAND STATE 
                         * COMMAND STATE CAN BE: NONE      = 0
                         *                       ERROR     = 1
                         *                       RECEIVED  = 2
                         *                       CHECKED   = 3
                         *                       PROCESSED = 4
                         *                       CONVERTED = 5
                         *                       Empty     = 6
                                                 Full      = 7 
                         */

typedef struct{
  long VoltageRMS;
   int VoltageMAX;
   int VoltageAVG;
}PowerVector;           /* DATA TYPE STRUCTURE POWERVECTOR
                         * PARAMETERS: VOLTAGERMS
                         *             VOLTAGEMAX
                         *             VOLTAGEAVG
                         */


#endif	/* _DATATYPES_H */

