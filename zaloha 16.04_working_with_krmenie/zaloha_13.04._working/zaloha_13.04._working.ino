#include "header1.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

DateTime now;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
RTC_DS1307 RTC;

/*Use Arduino millis() with buttons to delay events*/

unsigned long buttonPushedMillis; // when button was released
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 2500; // wait to turn on LED
unsigned long turnOffDelay = 5000; // turn off LED after this time
bool ledReady = false; // flag for when button is let go
bool ledState = false; // for LED is on or not.

void setup () {
  /*servo setting */
   //myservo.attach(9);  // attaches the servo on pin 9 to the servo object
   /*display seting***********/
   // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   
   /*RTC_setup************************/
    Serial.begin(9600);
    Wire.begin();
    RTC.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
    //RTC.adjust(DateTime(2017, 4, 2, 13, 57, 0)); 
    /*  GPIO pins setup*/
    
  }
 pinMode(13, OUTPUT); ;/*1_rele*/
 pinMode(8, OUTPUT); /*2_rele*/
 pinMode(7, OUTPUT); /*3_rele*/
 pinMode(A2, INPUT); /*botton 1*/
 pinMode(A1, INPUT); /*botton 2*/
 pinMode(A3, INPUT); /*botton 3*/
  pinMode(A0, INPUT); /*botton 3*/
  digitalWrite(7, HIGH);   // turn the OFF Cerpadlo
  digitalWrite(13, HIGH);  // turn the OFF Cerpadlo 
   digitalWrite(8, HIGH);   // turn the OFF Cerpadlo 
   
}
State_t state;
int pos = 0;
int countBotton_Cerp = 0;
int countBotton_Svetl = 0;
int countBotton_Filt = 0;

void loop () {
     now = RTC.now(); 
     LCD_print_times();
     
rele_ON_OFF_switch(ON_filt_hour,ON_filt_min,OFF_filt_hour,OFF_filt_minit,ON_filter,OFF_filter);

rele_ON_OFF_switch(ON_Cerp_hour,ON_Cerp_min,OFF_Cerp_hour,OFF_Cerp_min,ON_cerpadlo,OFF_cerpadlo);

krmenie_ON_switch(ON_krmenie_hour_1,ON_krmenie_minit_1,ON_krmenie_second_1,krmenie);

//krmenie_ON_switch(ON_krmenie_hour_2,ON_krmenie_minit_2,krmenie);


  if(analogRead(A1)> 1000)
{
  if (countBotton_Svetl == 0)
  {
  state = ON_svetlo;
  countBotton_Svetl = 1;
  }
  else if(countBotton_Svetl == 1)
  {
    state = OFF_svetlo;
countBotton_Svetl = 0;
  }
}
else if(analogRead(A2)> 1000)
{
  if (countBotton_Cerp == 0)
  {
  state = ON_cerpadlo;
  
  
  countBotton_Cerp = 1;
  }
 else if(countBotton_Cerp == 1)
  {
   state = OFF_cerpadlo;
   
   countBotton_Cerp = 0;
  }
}
else if(analogRead(A3)> 1000)
{
  if (countBotton_Filt == 0)
  {
  state = ON_filter;
  countBotton_Filt = 1;
 }
 else if(countBotton_Filt == 1)
  {
   state = OFF_filter;
   countBotton_Filt = 0;
 }
}

switch(state)
  { 
  case ON_cerpadlo:
  lcd.setCursor(9, 1);
  lcd.print("         ");    /*9 cols */
  lcd.setCursor(9, 1);
  lcd.print("ON_CERP");
  digitalWrite(13, LOW);  // turn the ON Cerpadlo 
  state = Default; 
  break;

  case OFF_cerpadlo:
  lcd.setCursor(9, 1);
  lcd.print("        ");  /*8 cols */
  lcd.setCursor(9, 1);
  lcd.print("OFF_CERP");
  digitalWrite(13, HIGH);  // turn the ON Cerpadlo 
  state = Default; 
  break;

  case ON_svetlo:
  lcd.setCursor(9,0);
  lcd.print("         ");   /*9 cols */
  lcd.setCursor(9,0);
  lcd.print("ON_SVETL");
  digitalWrite(8, LOW);   // turn the ON Cerpadlo 
  state = Default; 
  break;

  case OFF_svetlo:
  lcd.setCursor(9, 0);
  lcd.print("        ");   /*8 cols */
  lcd.setCursor(9, 0);
  lcd.print("OFF_SVETL");
  digitalWrite(8, HIGH);   // turn the ON Cerpadlo 
  state = Default; 
  break;

  case ON_filter:
  lcd.setCursor(0, 1);
  lcd.print("         ");  /*9 cols */
  lcd.setCursor(0, 1);
  lcd.print("ON_FILT");
  digitalWrite(7, LOW);    // turn the ON Cerpadlo 
  state = Default; 
  break;

  case OFF_filter:
  lcd.setCursor(0, 1);
  lcd.print("         ");   /*8 cols */
  lcd.setCursor(0, 1);
  lcd.print("OFF_FILT");
  digitalWrite(7, HIGH);   // turn the ON Cerpadlo 
  state = Default; 
  break;
  
  case krmenie:
  {
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees  in steps of 1 degree */
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
      }
     for (pos = 180; pos >= 0; pos -= 1) 
       {                                    // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
       }
       myservo.detach();
       state = Default; 
  }
      break;
       case Default:
       {
        break;
       }
  }
 
 }
void LCD_print_times(void)
{
  lcd.setCursor(0, 0);
  lcd.print(now.hour(), DEC);
  lcd.setCursor(2, 0);
  lcd.print(":");
  lcd.setCursor(3, 0);
  lcd.print(now.minute(), DEC);
  lcd.setCursor(5, 0);
  lcd.print(":");
  lcd.setCursor(6, 0);
  lcd.print(now.second(), DEC);
  // Turn off the display:
  
  // Turn on the display:
  lcd.display();
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("        ");    /*8 cols*******/
 }

void krmenie_ON_switch(int ON_hour,int ON_minute,int ON_second, State_t ON)
{
  if(now.hour() == ON_hour && now.minute() == ON_minute && now.second() == ON_second)
    {
      state = ON;
    }
 }

void rele_ON_OFF_switch(int ON_hour,int ON_minute,int OFF_hour,int OFF_minute, State_t ON, State_t OFF)
{
if(now.hour() == ON_hour && now.minute() == ON_minute)
  {
     state = ON;
      
  }
else if(now.hour() == OFF_hour && now.minute() == OFF_minute)
  {
     state = OFF;
  }
}
