
#include "xgpio.h"
#include "xuartlite.h"
#include "sleep.h"

#include <stdio.h>

int main()
{
	    XUartLite UART;
	    XGpio input;
	    XGpio output;
	    unsigned char data = 0;


	    XUartLite_Initialize(&UART, XPAR_AXI_UARTLITE_0_DEVICE_ID);
	    XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);	//initialize output XGpio variable
	    XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	//initialize input XGpio variable

	    XGpio_SetDataDirection(&input, 1, 0xF);			//set first channel tristate buffer to input
	    XGpio_SetDataDirection(&output, 1, 0x0);

	    while(1)
	    {
			data = XGpio_DiscreteRead(&input,1);

			XGpio_DiscreteWrite(&output, 1, data);

			XUartLite_Send(&UART, data, 1);

			usleep(100000);

	    }


	    return 0;
}

