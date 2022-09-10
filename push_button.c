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
#define SER1_595 GP4	//serial data in pin 14 for most signifcant digit
#define SER_595 GP0	//serial data in pin 14
#define RCLK_595 GP1	//storage register clock input pin 12 "latch"
#define SCLK_595 GP2	//shift register clock input pin 11 "storage"
/*========= Globals=========*/

char data[10] = {0x3F,0x4F,};
//1->0x30;2->0x5B;3->0x4F;4->0X66; ;5->0x6D;6->0X7D;7->0X47;8->0X7F;9->0X4F;0->0X3F
/* ======== Function space ==========*/

/* Delay function */
 
void delay (unsigned int tiempo);
/* floor function for most significant digit*/
int floorm(int num)
{
	int Dig = 0;
 	while((num-=10)>=0)
 	{
 		Dig++;
 
 	}
	return Dig;

}

/* setup function*/
void setup (void)
{
	ADCON0 = 0x00;
	ANSEL = 0x00;
	CMCON = 0x07; //shut off comparator
	VRCON = 0X00;
	TRISIO = 0X20;	// set all GPIOs as outputs, except GP5= push button
	GPIO = 0x20;	// set all pins low except GP5 

}

/* sclock:
 * This function will enable the storage clock to 74HC695
 */

void sclock(void)
{
	SCLK_595 =1;
	delay(10);
	SCLK_595 = 0;
	delay(10);


}

/* rclock:
 * This function will strobe/latch and enable the output trigger of 74HC695	
 */
void rclock(void)
{
	RCLK_595 =1;
	delay(10);
	RCLK_595 = 0;
	//delay(500);


} 
 
/* data display:
 * Thiss function will send the data to the serial line 74HC595 
 */
void data_display(int data)
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

    unsigned int time = 100;
    
    int rand0 = 0;
    int rand1 = 0;
    setup();
 
    //Loop forever
    //GP0 = 0x00;
    delay(time);
    
    while(1)
    {	
    	for(int i=0;i<100;i++)
	{

		rand0 = i;
		if(push_button == 0)
		{
			int rand0 = i%10;
			int rand1 = floorm(i);
			//1->0x30;2->0x5B;3->0x4F;4->0X66; ;5->0x6D;6->0X7D;7->0X47;8->0X7F;9->0X4F;0->0X3F
			switch(rand0)
			{	case 0:
				data_display(0x3F);
				break;
				case 1:
				data_display(0x30);
				break;
				case 2:
				data_display(0x5);
				break;
				case 3:
				data_display(0x4F);
				break;
				case 4:
				data_display(0X66);
				break;
				case 5:
				data_display(0x6D);
				break;
				case 6:
				data_display(0X7D);
				break;
				case 7:
				data_display(0X47);
				break;
				case 8:
				data_display(0X7F);
				break;
				case 9:
				data_display(0X4F); 
				break;		
		
			}
		
		}
	}

    }
    return;
}

void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
