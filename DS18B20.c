#ifndef DS18B20_C
#define DS18B20_C
#include "1_day.c"
#include <display.c>
int ds18b20_read(byte tem);
void ds18b20_configure(int8 TH, int8 TL, int8 config);

/*
 * ds1820_read()
 * Description: reads the ds18x20 device on the 1-wire bus and returns
 *              the temperature
 */
 
int ds18b20_read(byte tem) {
    int8 busy=0, temp1, temp2;
    signed int16 temp3;
    int result;
    onewire_reset();//1ms
    onewire_write(0xCC);//512us            //Skip ROM, address all devices
    onewire_write(0x44);//512us //Start temperature conversion    
    while(busy == 0){
       display_tem(tem);//Wait while busy (bus is low)
       edit_time();        
       busy = onewire_read();                
    }
    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0xBE);            //Read scratchpad
    temp1 = onewire_read();//1040us
    temp2 = onewire_read();    
    temp3 = make16(temp2, temp1);

    //result = (float) temp3 / 2.0;   //Calculation for DS18S20 with 0.5 deg C resolution
    result = temp3 >> 4;    //Calculation for DS18B20 with 0.1 deg C resolution
    return(result);
}

/*
 * ds1820_configure(int8 TH, int8 LH, int8 config)
 * Description: writes configuration data to the DS18x20 device
 * Arguments: alarm trigger high, alarm trigger low, configuration
 */

void ds18b20_configure(int8 TH, int8 TL, int8 config) {
    onewire_reset();
    onewire_write(0xCC);            //Skip ROM, address all devices
    onewire_write(0x4E);            //Write to scratchpad
    onewire_write(TH);
    onewire_write(TL);
    onewire_write(config);
}

#endif /*DS1820_C*/
