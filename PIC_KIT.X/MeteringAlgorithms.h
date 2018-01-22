
/*
 * File:   MeteringAlgorithms.h
 * Author: Michal
 *
 * Created on 24. 6. 2016, 10:19
 */

#ifndef METERINGALGORITHMS_H
#define	METERINGALGORITHMS_H

#include <plib.h>
#include <math.h>
#include "datatypes.h"

#define SamplesRMS              128                                             /* NUMBER OF SAMPLES (SHOULD BE 32, 64, 128)         */

#define VoltageCoef             0.3938                                          /* VOLTAGE CONSTANT                                  */
#define VoltageOffset           511                                             /* VOLTAGE OFFSET                                    */
#define VoltageAvgCoef          0.637                                           /* VOLTAGE AVERAGE CONSTANT                          */

#define SQRT2                   1.414221                                        /* ROOT 2                                            */
#define SCALEFACT               10                                              /* SCALE FACTOR                                      */

#if(SamplesRMS == 32)
    #define DIVFACT 5
    #define INCFACT (128/SamplesRMS)
#elif(SamplesRMS == 64)
    #define DIVFACT 6
    #define INCFACT (128/SamplesRMS)
#elif(SamplesRMS == 128)
    #define DIVFACT 7
    #define INCFACT (128/SamplesRMS)
#else
    #error "SamplesRMS should be 32, 64 or 128"
#endif

PowerVector Vector;
long Result;


/*
 * @function RMS_Calc
 * @brief    Calculation of RMS value from samples
 * @param    *Samples
 * @return   None
 */
void RMS_Calc(int *Samples);

/*
 * @function MAX_Calc
 * @brief    Calculation of Maximum voltage value
 * @param    None
 * @return   None
 */
void MAX_Calc(void);

/*
 * @function AVG_Calc
 * @brief    Calculation of Average voltage value
 * @param    None
 * @return   None
 */
void AVG_Calc(void);

#endif	/* METERINGALGORITHMS_H */

