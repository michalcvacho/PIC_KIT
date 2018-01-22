/* 
 * File:   protocol.c
 * Author: michal.cvacho
 *
 * Created on Pondelok, 2018, januára 22, 10:36
 */

#include "protocol.h"
#include "Uart.h"
#include "Adc.h"
int Temp;
/*
 * @function CheckRxMessage
 * @brief    Check Format and Convertion of Received Message
 * @param    *Data
 * @return   None
 */
void CheckRx2Message(char *Data2){
    
    unsigned int Err;/*mozny problem*/
    unsigned int Steps = 0; /*mozny problem*/
    unsigned int i;
    
    Err = 0;
    
   
    
    for(i = 0; i < (MessageLenght - 1); i++)
    {
        if(i == 0)
        {
            switch(*(Data2 + i))
            {
                case '<':   /* Command */  break;                   
                default:    Err = 1;       break;
            }
        }
        else if(i == 1)
        {
            switch(*(Data2 + i))
            {
                case 'A':   /* Command */  break;
                case 'M':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 2)
        {
            switch(*(Data2 + i))
            {
                case 'S':   /* Command */  break;
                case 'C':   /* Command */  break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 3)
        {
            switch(*(Data2 + i))
            {
                case 'L':   /* Command */  break;
                case 'R':   /* Command */  break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 4)
        {
            switch(*(Data2 + i))
            {
                case 'H':   /* Command */  break;
                case 'F':   /* Command */  break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 5)
        {
            switch(*(Data2 + i))
            {
                case '0':   Steps = 0;     break;
                case '1':   Steps = 100;   break;
                case '2':   Steps = 200;   break;
                case '3':   Steps = 300;   break;
                case '4':   Steps = 400;   break;
                case '5':   Steps = 500;   break;
                case '6':   Steps = 600;   break;
                case '7':   Steps = 700;   break;
                case '8':   Steps = 800;   break;
                case '9':   Steps = 900;   break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 6)
        {
            switch(*(Data2 + i))
            {
                case '0':   Steps += 0;    break;
                case '1':   Steps += 10;   break;
                case '2':   Steps += 20;   break;
                case '3':   Steps += 30;   break;
                case '4':   Steps += 40;   break;
                case '5':   Steps += 50;   break;
                case '6':   Steps += 60;   break;
                case '7':   Steps += 70;   break;
                case '8':   Steps += 80;   break;
                case '9':   Steps += 90;   break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 7)
        {
            switch(*(Data2 + i))
            {
                case '0':   Steps += 0;    break;
                case '1':   Steps += 1;    break;
                case '2':   Steps += 2;    break;
                case '3':   Steps += 3;    break;
                case '4':   Steps += 4;    break;
                case '5':   Steps += 5;    break;
                case '6':   Steps += 6;    break;
                case '7':   Steps += 7;    break;
                case '8':   Steps += 8;    break;
                case '9':   Steps += 9;    break;
                case '-':   /* Command */  break;
                default:    Err = 1;       break;
            }
        }
        else if(i == 8)
        {
            switch(*(Data2 + i))
            {
                case '>':   /* Command */  break;                   
                default:    Err = 1;       break;
            }
        }
    }
    
    if(Err == 0)
    {       
        //if(*(Data+1) == 'A')
        /*{
           // ControlParams.Mode = Automatical;
        }
        /*else if(*(Data+1) == 'M')
        {
           //ControlParams.Mode = Manual;
        }
        
        /*ControlParams.SetClear  = *(Data + 2);
        ControlParams.Direction = *(Data + 3);
        ControlParams.HalfFull  = *(Data + 4);
        ControlParams.NumSteps  = Steps;*/
        //CommandReceiveFlagUART_2 = Received;
        MessageCheckFlag = Checked;
        
        BufferTx2[0]='o';
        BufferTx2[1]='k';
        BufferTx2[2]=' ';
        BufferTx2[3]=' ';
        BufferTx2[4]=' ';
       
    }
    else if(Err == 1)
    {
    
        /*ControlParams.NumSteps  = 0;
        ControlParams.Mode      = Manual;
        ControlParams.SetClear  = '-';
        ControlParams.Direction = '-';
        ControlParams.HalfFull  = '-';*/
        
        MessageCheckFlag = Error;
        BufferTx2[0]='e';
        BufferTx2[1]='r';
        BufferTx2[2]='r';
        BufferTx2[3]='o';
        BufferTx2[4]='r';
      
    }
}



void CheckRx3Message(char *Data3){
    
    unsigned int Err   = 0; /*mozny problem*/
    unsigned int percent = 0; /*mozny problem*/
    unsigned int i;
  
    for(i = 0; i < (MessageLenght - 1); i++)
    {
        if(i == 0)
        {
            switch(*(Data3 + i))
            {
                case '<':   BufferTx2[i]= '<'; break;                   
                default:    Err = 1;           break;
            }
        }
        else if(i == 1)
        {
            switch(*(Data3 + i))
            {
                case 'A':    BufferTx2[i]='A';  break;
                case 'M':    BufferTx2[i]='M'; break;
                default:     Err = 1;       break;
            }
        }
        else if(i == 2)
        {
            switch(*(Data3 + i))
            {
                case 'B':   BufferTx2[i]='B';   break;
                case 'N':   BufferTx2[i]='N';   break;
                default:    Err = 1;            break;
            }
        }
        else if(i == 3)
        {
            switch(*(Data3 + i))
            {
                case 'L':   BufferTx2[i]='L';  break;
                case 'R':   BufferTx2[i]='R';  break;
                case '-':   BufferTx3[i]='-';  break;
                default:    Err = 1;           break;
            }
        }
        else if(i == 4)
        {
            switch(*(Data3 + i))
            {
                case 'H':   BufferTx2[i]='H';  break;
                case 'F':   BufferTx2[i]='F';  break;
                case '-':   BufferTx3[i]='-';  break;
                default:    Err = 1         ;  break;
            }
        }
        else if(i == 5)
        {
            switch(*(Data3 + i))
            {
               case '0':    percent = 0 ;       BufferTx2[i]='0';   break;
               case '1':    percent = 100;      BufferTx2[i]='1';   break;
               case '2':    percent = 200;      BufferTx2[i]='2';   break;
               default:     Err = 1;                                 break;
            }
        }
        else if(i == 6)
        {
            switch(*(Data3 + i))
            {
                case '0':   percent += 0;   BufferTx2[i]='0'; break;
                case '1':   percent += 10;  BufferTx2[i]='1'; break;
                case '2':   percent += 20;  BufferTx2[i]='2'; break;
                case '3':   percent += 30;  BufferTx2[i]='3'; break;
                case '4':   percent += 40;  BufferTx2[i]='4'; break;
                case '5':   percent += 50;  BufferTx2[i]='5'; break;
                case '6':   percent += 60;  BufferTx2[i]='6'; break;
                case '7':   percent += 70;  BufferTx2[i]='7'; break;
                case '8':   percent += 80;  BufferTx2[i]='8'; break;
                case '9':   percent += 90;  BufferTx2[i]='9'; break;  
                default:    Err = 1;     break;
            }
        }
        else if(i == 7)
        {
            switch(*(Data3 + i))
            {
                case '0':   percent += 0;   BufferTx2[i]='0'; break;
                case '1':   percent += 1;   BufferTx2[i]='1'; break;
                case '2':   percent += 2;   BufferTx2[i]='2'; break;
                case '3':   percent += 3;   BufferTx2[i]='3'; break;
                case '4':   percent += 4;   BufferTx2[i]='4'; break;
                case '5':   percent += 5;   BufferTx2[i]='5'; break;
                case '6':   percent += 6;   BufferTx2[i]='6'; break;
                case '7':   percent += 7;   BufferTx2[i]='7'; break;
                case '8':   percent += 8;   BufferTx2[i]='8'; break;
                case '9':   percent += 9;   BufferTx2[i]='9'; break;
                default:    Err = 1;                          break;
            }
        }
        else if(i == 8)
        {
            switch(*(Data3 + i))
            {
                case '>':   BufferTx2[i]='>';  break;                   
                default:    Err = 1;           break;
            }
        }
    }
    
    if(Err == 0)
    	
             {       
        MessageCheckFlag = Checked;
       	BufferTx3[10]=' ';
        BufferTx3[11]='o';
        BufferTx3[12]='k';
        BufferTx3[13]=' ';
        BufferTx3[14]=' ';
            }
        else if(Err == 1)
            {
       	BufferTx3[10]=' ';
        BufferTx3[11]='e';
        BufferTx3[12]='r';
        BufferTx3[13]='r';
        BufferTx3[14]='o';
            }
}

/*
 * @function ConvertTxMessage
 * @brief    Convert State Machine Message
 * @param    *Data
 * @return   None
 */
/*void ConvertTxMessage(char *Data)
{
    
    MessageConvertedFlag = None;
    
        *(Data + 0) = '<';  /* Start message */
    
    /*if(ControlParams.Mode == Manual)
    {
        *(Data + 1) = 'M';
    }
    else if(ControlParams.Mode == Automatical)
    {
        *(Data + 1) = 'A';
    }
    
    if(LimitSwitchH == closed)
    {
        *(Data + 2) = 'C';
    }
    else if(LimitSwitchH == opened)
    {
        *(Data + 2) = 'O';
    }
    
    if(LimitSwitchL == closed)
    {
        *(Data + 3) = 'C';
    }
    else if(LimitSwitchL == opened)
    {
        *(Data + 3) = 'O';
    }
    
    if(StepperMotorBussyFlag == Bussy)
    {
        *(Data + 8) = 'B';
    }
    else if(StepperMotorBussyFlag == Ready)
    {
        *(Data + 8) = 'R';
    }
    
    *(Data + 9) = '>'; /* End of message */
    
    //MessageConvertedFlag = Converted;
//}