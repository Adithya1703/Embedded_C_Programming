#include "uart.h"
#include "stm32f411xe.h"
/*uint32_t *portAHB1ENR = (uint32_t*)0x40023830;
uint32_t *portAPB1ENR = (uint32_t*)0x40023840;
uint32_t *GPIOA_MODER = (uint32_t*)0x4002000;
uint32_t *GPIOA_AFRL = (uint32_t*)0x40020020;
uint32_t *USART2_SR = (uint32_t*)0x40004400;
uint32_t *USART2_DR = (uint32_t*)0x40004404;
uint32_t *USART2_BRR = (uint32_t*)0x40004408;
uint32_t *USART2_CR1 = (uint32_t*)0x4000440C;*/

void uart2_tx_init(void)
{
	//Enabling Clock access to GPIOA
	//*portAHB1ENR|=GPIOAEN; //enables GPIOAEN in RCC
	RCC->AHB1ENR |= GPIOAEN; //alternate with usage of header for above

	//SET GPIOA - PA2 Mode to Alternate Function mode
	//*GPIOA_MODER&=~(1U<<4); //sets 0 at MODER pos 4 for PA2
	//*GPIOA_MODER|=(1U<<5); //sets 1 at MODER pos 5 for PA
	GPIOA->MODER &=	~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	//SET GPIOA - PA2 Alternate function type to be USART_TX(AF07)
	//*GPIOA_AFRL|=(1U<<8); //sets PA2 alternate function type to UART_TX(AF07(0111 at PA2) - function type as per data sheet)
	//*GPIOA_AFRL|=(1U<<9); //sets PA2 alternate function type to UART_TX(AF07(0111 at PA2) - function type as per data sheet)
	//*GPIOA_AFRL|=(1U<<10); //sets PA2 alternate function type to UART_TX(AF07(0111 at PA2) - function type as per data sheet)
	//*GPIOA_AFRL&=~(1U<<11); //sets PA2 alternate function type to UART_TX(AF07(0111 at PA2) - function type as per data sheet)
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	//Configure USART CLOCK Access
	//*portAPB1ENR|=UART2EN; //17 is the bit pos of USART2 in APB1ENR RCC to enable USART2 clk access
	RCC->APB1ENR=UART2EN;

	//Configure Baudrate
	//*USART2_BRR=compute_USART_BRR(APB1_CLK, UART_BAUDRATE); //formula to compute BRR of USART2
	USART2->BRR=compute_USART_BRR(APB1_CLK, UART_BAUDRATE);

	//Configure transfer direction in CR1(control register1)(TE(transmit for PA2) - Bit 3)
	//*USART2_CR1=0x0008;
	USART2->CR1=CR1_TE;

	//Also enable USART enable bit 13 in CR1
	//*USART2_CR1|=0x2000;
	USART2->CR1|=CR1_UE;
}

uint32_t compute_USART_BRR(uint32_t PeripheralCLK, uint32_t Baudrate)
{
	return ((PeripheralCLK+(Baudrate/2U))/Baudrate);
}




void uart2_write(int ch){
	//check whether USART2_SR is empty, if its not empty then we can wirte to data register this is done by checking whether ORE(overrun) is 1 or not
	while(!(USART2->SR&SR_TXE)){
		USART2->DR = (ch&0xFF);
	}

	// another way to check whether to send data to DataRegister
	/* while(!(*USART_SR&0x0080)){}
	 * this will ensure that data gets sent when DR is empty
	 */
}
