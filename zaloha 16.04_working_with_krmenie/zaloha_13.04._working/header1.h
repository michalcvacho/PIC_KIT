#ifndef header1_h
#define header1_h


/*cerpadlo times*/
#define ON_Cerp_hour 11
#define ON_Cerp_min 00
#define OFF_Cerp_hour 15
#define OFF_Cerp_min 00

/*filter times*/
#define ON_filt_hour  10
#define ON_filt_min   20
#define OFF_filt_hour 16
#define OFF_filt_minit 00

/*krmenie times*/
#define ON_krmenie_hour_1  10
#define ON_krmenie_minit_1  00

#define ON_krmenie_hour_2  20
#define ON_krmenie_minit_2  15
//DateTime now;
typedef  enum {
  krmenie,
  ON_cerpadlo,
  OFF_cerpadlo,
  ON_svetlo,
  OFF_svetlo,
  ON_filter,
  OFF_filter,
  Default
  } State_t ;
void LCD_print_times(void);
//void krmenie_ON_switch(int ON_hour,int ON_minute, State_t ON);
void rele_ON_OFF_switch(int ON_hour,int ON_minute,int OFF_hour,int OFF_minute, State_t ON, State_t OFF);




 


#endif
