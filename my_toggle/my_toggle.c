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
				SysCtlDelay(10000000);	 	// Slow blinking by five times

        // Toggle the LED.
        GPIO_PORTF_DATA_R ^=GREEN_MASK;
    }
}
