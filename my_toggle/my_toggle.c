#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define 	GREEN_MASK 		0x08  		// Define green_mask as PF3
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
    GPIO_PORTF_AMSEL_R &= ~0x00;				// clear AMSEL (disable analog mode selection)
    GPIO_PORTF_PCTL_R &= ~0x00000000;		// PCTL GPIO on PF7-0, select GPIO, clear all
    GPIO_PORTF_AFSEL_R &= ~0x00; 				// clear AFSEL bits to 0 to select regular I/O
	
    //
    // Enable the GPIO pin for the red LED (PF1).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIO_PORTF_DIR_R |= 0x08;	// enable GPIO pin for green LED (PF3), set direction as output
    GPIO_PORTF_DEN_R |= 0x08;	// enable pin for digital function

}


int main(void)
{
	
		//initialize the GPIO ports	
		PortFunctionInit();
	
    // Turn on the LED.
    GPIO_PORTF_DATA_R |= 0x08; 		// Green

    
    //
    // Loop forever.
    //
    while(1)
    {
        // Delay for a bit.
				SysCtlDelay(10000000);	 	// Slow blinking by five times, 10000000 loops 
								// each loop is 3 CPU cycles 10M*3/16M = 1.875 sec
        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=GREEN_MASK;
    }
}
