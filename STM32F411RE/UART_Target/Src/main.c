#include "uart.h"

int main(void)
{
	//Enable clock on both buses of GPIOA and USART2
    //Calibrate Moder and Alternate functions of GPIOA
    //Configure USART2 data registers, BRR(baud rate) and SR(status register)and CR1(control register to enable)
	uart2_tx_init();

	while(1){
		uart2_write('A');
	}

}






