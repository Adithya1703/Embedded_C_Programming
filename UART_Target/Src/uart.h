/*
 * uart.h
 *
 *  Created on: Jan 4, 2025
 *      Author: hp
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#define GPIOAEN (1U<<0)
//PA2 - TX, PA3 - RX
#define UART2EN (1U<<17)

#define SYS_FREQ 16000000 //16 MHz common for nucleo board
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200

void uart2_tx_init(void);
uint16_t compute_USART_BRR(uint32_t PeripheralCLK, uint32_t Baudrate);
void uart2_write(int ch);



#endif /* UART_H_ */
