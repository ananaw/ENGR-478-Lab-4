#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define 	GREEN_MASK 		0x08
//*****************************************************************************
//
//!
//! A very simple example that toggles the on-board red LED using direct register
//! access.
//
//*****************************************************************************


void
PortFunctionInit(void)
{
//
		volatile uint32_t ui32Loop;   
	// Enable the GPIO port that is used for the on-board LED.
    //
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    //
    // Do a dummy read to insert a few cycles after enabling the peripheral.
    //
    ui32Loop = SYSCTL_RCGC2_R;
		GPIO_PORTF_LOCK_R = 0x4C4F434B;    //unlcok PF   
	
    GPIO_PORTF_AMSEL_R &= ~0x00;				// clear AMSEL (disable analog mode selection)
    GPIO_PORTF_PCTL_R &= ~0x00000000;		// PCTL GPIO on PF7-0, select GPIO, clear all
    GPIO_PORTF_AFSEL_R &= ~0x00; 				// clear AFSEL bits to 0 to select regular I/O
    //
    // Enable the GPIO pin for the red LED (PF1) AND GREEN LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function. 
    //
    GPIO_PORTF_DIR_R |= 0x0A; 		// set PF3,PF1 as output (10)
		GPIO_PORTF_DIR_R &= ~0x10; 		// set PF4 as input
    GPIO_PORTF_DEN_R |= 0x1A;			// enable digital function for PF4,3,1
		//Enable internal pull-up on PF4
		GPIO_PORTF_PUR_R |= 0x10; 

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    // Turn on the LED.
    GPIO_PORTF_DATA_R |= 0x08; // PF3
		
    
    //
    // Loop forever.
    //
    while(1)
    {
        
			if ((GPIO_PORTF_DATA_R&0x10) == 0x00) // if PF4 is pressed
			{
			SysCtlDelay(2000000);		      // delay for 0.375 sec
			GPIO_PORTF_DATA_R ^= 0x0A;	      // toggle PF3 & PF1 (yellow)
			}
			
			else 
			{
				//GPIO_PORTF_DATA_R &= ~0x02;
				// Delay for a bit.
				SysCtlDelay(2000000);		

        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=GREEN_MASK;				// Toggle PF3, green only
			}
    }
}
