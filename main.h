#include <16F887.h>
#device ADC=8
#FUSES HS
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=8000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#byte portb=0x06
#byte trisb=0x86
#byte ANSEL=0x188
#byte ANSELH=0x189
#bit trisb0=trisb.0
#bit trisb4=trisb.4
#bit trisb5=trisb.5
