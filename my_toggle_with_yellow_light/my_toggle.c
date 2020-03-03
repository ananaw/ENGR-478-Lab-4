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
    //
    // Enable the GPIO pin for the red LED (PF1) AND GREEN LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function. 
    //
    GPIO_PORTF_DIR_R |= 0x0A; 		// set pf3,pf1 as output 
		GPIO_PORTF_DIR_R &= ~0x10; 		// set pf4 as input
    GPIO_PORTF_DEN_R |= 0x1A;			// enable digital function for pf4,3,1
		//Enable pull-up on PF4
		GPIO_PORTF_PUR_R |= 0x10; 

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    // Turn on the LED.
    GPIO_PORTF_DATA_R |= 0x08; //pf3
		
    
    //
    // Loop forever.
    //
    while(1)
    {
        
			if ((GPIO_PORTF_DATA_R&0x10) == 0x00)
			{
			SysCtlDelay(2000000);
			GPIO_PORTF_DATA_R ^= 0x0A;
			}
			
			else 
			{
				//GPIO_PORTF_DATA_R &= ~0x02;
				// Delay for a bit.
				SysCtlDelay(2000000);	

        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=GREEN_MASK;
			}
    }
}
