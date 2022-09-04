#include <pic14/pic12f675.h>
#include <stdlib.h>

//#pragma config WDTE = OFF //WDT disabled 
//To compile:
//sdcc -mpic14 -p16f675 blink.c
 
//To program the chip using picp:
//Assuming /dev/ttyUSB0 is the serial port.
 
//Erase the chip:
//picp /dev/ttyUSB0 16f887 -ef
 
//Write the program:
//picp /dev/ttyUSB0 16f887 -wp blink.hex
 
//Write the configuration words (optional):
//picp /dev/ttyUSB0 16f887 -wc 0x2ff4 0x3fff
 
//Doing it all at once: erasing, programming, and reading back config words:
//picp /dev/ttyUSB0 16f887 -ef -wp blink.hex -rc
 
//To program the chip using pk2cmd:
//pk2cmd -M -PPIC16f887 -Fblink.hex

#define push_button GP5
 
void delay (unsigned inttiempo);

void setup (void)
{
	ADCON0 = 0x00;
	ANSEL = 0x00;
	CMCON = 0x00;
	VRCON = 0X00;
	TRISIO = 0X20;	// set all GPIOs as outputs, except GP5= push button
	GPIO = 0x20;	// set all pins low except GP5 

}
 
void main(void)
{

    unsigned int time = 1000;
    
    setup();
 
    //Loop forever
    //GP5 = 0x11;
    GP0 = 0x00;
    delay(time);
    while ( 1 )
    {
		//__delay_ms(75);    
    		if(push_button  == 0)
    		{
    		
    			//delay(time); 			
    
			GP0 = 0x11;
			//delay(time);

			//GP0 = ~GP0;
			//delay(time);
			  	
    		}
    }
 
}

void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
