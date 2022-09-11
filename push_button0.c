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


// Interfacing 74HC95 Serial Shift Register
#define push_button GP5	//push button
#define SER_595 GP0	//serial data in pin 14
#define RCLK_595 GP1	//storage register clock input pin 12 "latch"
#define SCLK_595 GP2	//shift register clock input pin 11 "storage"

/*========= Globals=========*/
char data[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

/* ======== Function space ==========*/

/* Delay function */
 
void delay (unsigned int tiempo);

/* setup function*/
void setup (void)
{
	ADCON0 = 0x00;
	ANSEL = 0x00;
	CMCON = 0x00;
	VRCON = 0X00;
	TRISIO = 0X20;	// set all GPIOs as outputs, except GP5= push button
	GPIO = 0x20;	// set all pins low except GP5 

}

/* Counter function*/
int contador(void)
{
	for(int i=0;i<10;i++)
	{
	
	return i;
	}

}

/* sclock:
 * This function will enable the storage clock to 74HC695
 */

void sclock(void)
{
	SCLK_595 =1;
	delay(500);
	SCLK_595 = 0;
	delay(500);


}

/* rclock:
 * This function will strobe/latch and enable the output trigger of 74HC695	
 */
void rclock(void)
{
	RCLK_595 =1;
	delay(500);
	RCLK_595 = 0;
	//delay(500);


} 
 
/* data display:
 * Thiss function will send the data to the serial line 74HC595 
 */
void data_display(unsigned int data)
{
	for(int i=0; i<8;i++)
	{
		SER_595 = (data >> i) & 0x01; // bit shift and bit mask.
		sclock(); // enable data storage clock
	
	
	}
	rclock(); // data latch

}


 
 /*======= Main loop ========*/
void main(void)
{

    unsigned int time = 500;
    unsigned int time2 = 50;
    setup();
 
    //Loop forever
    //GP0 = 0x00;
    //delay(time);
    data_display(0x3F);
    while ( 1 )
    {
    		data_display(data[4]);
		   
    		if(push_button  == 0)
    		{	
    			
    			data_display(data[0]);
    			
    		
    			delay(time); 			
    
			//GP0 = 0x11;
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
