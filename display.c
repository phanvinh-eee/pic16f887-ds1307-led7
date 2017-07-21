#ifndef DISPLAY_C
#define DISPLAY_C
#define LED1 PIN_A0
#define LED2 PIN_A1
#define LED3 PIN_A2
#define LED4 PIN_A3
#define LED5 PIN_A4
#define LED6 PIN_A5

#define MODE PIN_B0
#define EDIT PIN_C0
#define INC PIN_C2
#define DEC PIN_C3
//                      0    1    2    3    4    5    6    7    8    9   0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   C    do C off  
byte const DIGITS[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x39,0x63,0x00,};
int clock_mode=0;
int h_alarm=2, m_alarm=5;
int h=2,m=4,s=45;
int h_edit=0,m_edit=0;
byte day=5,mth=4,yea=15,dow=2;
byte set_alarm=1;
byte temp;
void off_on_led(byte pin);
void display_led(byte digit, byte pin);
void display_time_alarm_on(byte h,byte m, byte s);
void display_time(byte h,byte m, byte s);
void display_tem(byte i);
void display_edit_h_alarm_off(byte halarm, byte malarm, byte salarm);
void display_edit_m_alarm_off(byte halarm, byte malarm, byte salarm);
void display_edit_h_alarm_on(byte halarm, byte malarm, byte salarm);
void display_edit_m_alarm_on(byte halarm, byte malarm, byte salarm);
void delayled_on_edit(int time);
void delayled_on(int time);
void delayled_off(int time);
void clock_alarm();
void edit_time();

void off_on_led(byte pin) {
   output_low(pin);
   delay_ms(1);
   output_high(pin);
}

void display_led(byte digit, byte pin) {
   output_d(DIGITS[digit] ^ 0xff);
   off_on_led(pin);
}

void display_time_alarm_on(byte h,byte m, byte s) {//hien thi thoi gian khi alarm on
   display_led(s % 10+10, LED1);
   display_led(s / 10, LED2);   
   display_led(m % 10+10, LED3);
   display_led(m / 10, LED4);   
   display_led(h % 10+10, LED5);
   display_led(h / 10, LED6);
}
void display_time(byte h,byte m, byte s) {//hien thi thoi gian khi alarm off
   display_led(s % 10, LED1);
   display_led(s / 10, LED2);   
   display_led(m % 10, LED3);
   display_led(m / 10, LED4);   
   display_led(h % 10, LED5);
   display_led(h / 10, LED6);
}

void display_tem(byte i){//hien thi nhiet do
   display_led(i % 10, LED3);
   display_led(i / 10, LED4);
  
   display_led(21, LED2); //'
   display_led(20, LED1); //C
}

void display_edit_h_alarm_off(byte halarm, byte malarm, byte salarm){//hien thi man hinh khi dang dieu chinh phut
   int i=0;// khi alarm off
   for(i=0;i<30;i++){
      display_led(0, LED1);
      display_led(0, LED2);   
      display_led(malarm % 10, LED3);
      display_led(malarm / 10, LED4);   
      display_led(22, LED5);
      display_led(22, LED6);
   }
   for(i=0;i<30;i++)
      display_time(halarm, malarm, salarm);
}
void display_edit_m_alarm_off(byte halarm, byte malarm, byte salarm){//hien thi man hinh khi dang dieu chinh gio
   int i=0;//khi alarm off
   for(i=0;i<30;i++){
      display_led(0, LED1);
      display_led(0, LED2);   
      display_led(22, LED3);
      display_led(22, LED4);   
      display_led(halarm % 10, LED5);
      display_led(halarm / 10, LED6);
   }
   for(i=0;i<30;i++)   
      display_time(halarm, malarm, salarm);
}
void display_edit_h_alarm_on(byte halarm, byte malarm, byte salarm){
   int i=0;
   for(i=0;i<30;i++){
      display_led(10, LED1);
      display_led(0, LED2);   
      display_led(malarm % 10+10, LED3);
      display_led(malarm / 10, LED4);   
      display_led(22, LED5);
      display_led(22, LED6);
   }      
   for(i=0;i<30;i++)
      display_time_alarm_on(halarm, malarm, salarm);
}
void display_edit_m_alarm_on(byte halarm, byte malarm, byte salarm){
   int i=0;
   for(i=0;i<30;i++){
      display_led(10, LED1);
      display_led(0, LED2);   
      display_led(22, LED3);
      display_led(22, LED4);   
      display_led(halarm % 10+10, LED5);
      display_led(halarm / 10, LED6);
   }
   for(i=0;i<30;i++)   
      display_time_alarm_on(halarm, malarm, salarm);
}

void delayled_on_edit(int time){//hien thi man hinh khi o che do dieu chinh
   int i=0,j=0;
   for(i=0;i<time;i++)
   for(j=0;j<30;j++)
   if(set_alarm==0){
      switch(clock_mode){
         case 3: display_time(h_edit, m, 0);
                 break;
         case 4: display_time(h_edit, m_edit, 0);
                 break;
         case 5: display_time(h_alarm,m_alarm,0);
                 break;
         case 6: display_time(h_alarm,m_alarm,0);
                 break;
      }
   }else{
      switch(clock_mode){
         case 3: display_time_alarm_on(h_edit, m_edit, 0);
                 break;
         case 4: display_time_alarm_on(h_edit, m_edit, 0);
                 break;          
         case 5: display_time_alarm_on(h_alarm,m_alarm,0);
                 break;
         case 6: display_time_alarm_on(h_alarm,m_alarm,0);
                 break;
      }      
   }
}
void delayled_on(int time){//hien thi cac man hinh
   int i=0;
   for(i=0;i<time;i++)
   if(set_alarm==0){
      switch(clock_mode){
         case 0: display_time(h, m, s);                 
                 break;
         case 1: display_time(h_alarm, m_alarm, 0);
                 break;
         case 2: display_tem(temp);
                 break;                    
         case 3: display_edit_h_alarm_off(h_edit, m_edit, 0);
                 break;
         case 4: display_edit_m_alarm_off(h_edit, m_edit, 0);
                 break;          
         case 5: display_edit_h_alarm_off(h_alarm,m_alarm,0);
                 break;
         case 6: display_edit_m_alarm_off(h_alarm,m_alarm,0);
                 break;
      }
   }
      else{
      switch(clock_mode){
         case 0: display_time_alarm_on(h, m, s);         
                 break;
         case 1: display_time_alarm_on(h_alarm, m_alarm, 0);
                 break;
         case 2: display_tem(temp);
                 break;                    
         case 3: display_edit_h_alarm_on(h_edit, m_edit, 0);
                 break;
         case 4: display_edit_m_alarm_on(h_edit, m_edit, 0);
                 break;          
         case 5: display_edit_h_alarm_on(h_alarm,m_alarm,0);
                 break;
         case 6: display_edit_m_alarm_on(h_alarm,m_alarm,0);
                 break;
      }
      
      }
}

void delayled_off(int time){//man hinh tat tat ca cac led
   int i=0,j=0;
   for(i=0;i<time;i++)
      for(j=0;j<30;j++){  
         display_led(22, LED1);
         display_led(22, LED2);   
         display_led(22, LED3);
         display_led(22, LED4);   
         display_led(22, LED5);
         display_led(22, LED6);
      }
}
void clock_alarm(){//man hinh bao dong alarm trong 30s
   int i=0;   
   delayled_off(1);
  while(s<30){ 
      rtc_get_time(h, m, s);
//      printf("second %d ",s);
      for(i=0;i<30;i++)
      display_time_alarm_on(h, m, s);
      delayled_off(1);
      if(!input(MODE)){
         while(!input(MODE)){
            display_time_alarm_on(h, m, s);
         }
         break;
      }      
   }
}
void edit_time(){
      if(!input(MODE)){
         while(!input(MODE)){
            delayled_off(1);
         }
         if(clock_mode>=2) clock_mode=0;
         else clock_mode++;//chuyen sang cac che do        
      }
      
      if(!input(EDIT)){
         while(!input(EDIT)){
            delayled_off(1);
            //printf("point 1\n");
         }
         switch(clock_mode){
            case 6: clock_mode=1;//ve man hinh alarm                   
                    break;
            case 5: clock_mode=6;//khi dang dieu chinh gio cua alarm, chuyen sang dieu chinh phut                    
                    break;
            case 4: clock_mode=0;//ve man hinh hien thi thoi gian, luu gia tri cai dat
                    rtc_set_datetime(day,mth,yea,dow,h_edit,m_edit);
                    h=h_edit;
                    m=m_edit;
                    break;
            case 3: clock_mode=4;//khi dang dieu chinh gio, chuyen sang dieu chinh phut                    
                    break;
            case 1: clock_mode=5;//khi dang hien thi alarm hien thi che do dieu chinh alarm
                    break;
            case 0: clock_mode=3;//khi dang hien thi thoi gian chuyen sang che do dieu chinh thoi gian
                    h_edit=h;
                    m_edit=m;
                    break;         
         }
//         printf("point 1\n");
//         delayled_on(1);
      }
      
      if(!input(INC)){         
         while(!input(INC)){
            delayled_on_edit(1);
            if(clock_mode==3){//man hinh dieu chinh gio
               h_edit++;//dieu chinh gio
               if(h_edit>23)h_edit=0;               
            }
            else if(clock_mode==4){//man hinh dieu chinh phut
               m_edit++;//dieu chinh phut
               if(m_edit>59) m_edit=0;                
            }    
            else if(clock_mode==1) set_alarm=1;//neu dang man hinh alarm, set alarm on
            else if(clock_mode==5){//man hinh dieu chinh gio alarm
               h_alarm++;//dieu chinh gio alarm
               if(h_alarm>23) h_alarm=0;
            }
            else if(clock_mode==6){//man hinh dieu chinh phut
               m_alarm++;//dieu chinh phut
               if(m_alarm>59) m_alarm=0;
            } 
            
         }
      }
      
      if(!input(DEC)){//khi bam nut giam gia tri         
         while(!input(DEC)){
            delayled_on_edit(1);            
            if(clock_mode==1) set_alarm=0;//man hinh hien thi alarm, set alarm off
            else if(clock_mode==3){//man hinh dieu chinh gio           
                if(h_edit==0) h_edit=23;
                else h_edit--;//dieu chinh gio               
            }
            else if(clock_mode==4){           
                if(m_edit==0) m_edit=59;                  
                else m_edit--;//dieu chinh phut
            }
            else if(clock_mode==5){           
               if(h_alarm==0) h_alarm=23;
                else h_alarm--;//dieu chinh gio alarm
            }
            else if(clock_mode==6){           
               if(m_alarm==0) m_alarm=59;
               else m_alarm--;//dieu chinh phut              
            }    
         }
      }
}
#endif
