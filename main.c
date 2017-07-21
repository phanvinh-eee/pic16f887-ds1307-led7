#include <main.h>
//#include <lcd.c>
#include <ds1302.c>
#include <ds18b20.c>


void main()
{
   byte count=0;
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_spi(FALSE);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   rtc_init();//khoi tao dong ho
//   rtc_set_datetime(day,mth,yea,dow,h,m);      
   
  while(TRUE) 
  {
      rtc_get_time(h, m, s); //lay thoi gian
      rtc_get_date(day,mth,yea,dow);//lay gia tri ngay thang
      edit_time();//ham quet phim     

      if(clock_mode==2){//man hinh hien thi nhiet do, lay nhiet do tu ds18b20
         temp=ds18b20_read(temp);
      }

      if(set_alarm==1)//kiem gia alarm set hay khong
         if(h==h_alarm)
           if(m==m_alarm)
            if(s==0){
               clock_alarm();//man hinh bao dong alarm
            }            
      delayled_on(1);//man hinh hien thi
//      printf("day: %d, month: %d, year: %d, day of week: %d\n",day,mth,yea,dow);     
  }
}

