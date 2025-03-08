

#include <stdint.h>
#include "stm32f411xe.h"

/*PC0 - PC07 --D0-D7(LCD)
 *PB5 - RS(regiser select)
 *PB6 - RW(read/write)
 *PB7 - EN(Enable)
 */

#define RW (1U << 6) //MSB and LSB -  PB6(0100 0000)
#define RS (1U << 5) //For port B5(0010 0000)
#define EN (1U << 7)
unsigned char message[]="hello world";
void delayMS(int delay);
void GPIO_init(void);
void LCD_Command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);

int main(void)
{
	LCD_init();
	/* Loop forever */
	for(;;);
}

void GPIO_init(void){
	//Enable Bus for Port B and C
	RCC->AHB1ENR|=0x06; //0000 0110(B&C)

	//Set Output mode for PIN B and C
	GPIOB->MODER |=0x5400; //01 - output mode for moder 5,6,7 moders as per data sheet
	GPIOC->MODER |=0x00005555; //01 output mode for 0-7 moders (8-15 = 0)

	//SET bit for EN and RW to low
	GPIOB->BSRR = 0x00C; //13(bit 6 and 7)
}

void LCD_Command(unsigned char command){
	/*to reset pb5 and pb6 to 0 to update command to odr(0-15 -set), (16-31 - reset pins)
	 * RS=0 - command; RS=1 - data
	 * RW=0 - write; RW=1 - read
	 */
	GPIOB->BSRR=(RS|RW)<<16; //((1U<<5)|(1U<<6)<<16)

	//Set command data to ODR(pin C0-C7)
	GPIOC->ODR=command;

	//Latch the LCD to ODR so that it process command
	GPIOB->BSRR=EN; //enable-1
	delayMS(15);

	//Reset EN
	GPIOB->BSRR=EN<<16; //reset-0
	delayMS(15);
}

void LCD_data(unsigned char data){

	GPIOB->BSRR=RS; //RS=1 to send data

	GPIOB->BSRR=RW<<16; //RW=0 to write

	//Set command data to ODR(pin C0-C7)
	GPIOC->ODR=data;

	//Latch the LCD to ODR so that it process command
	GPIOB->BSRR=EN; //enable -1
	delayMS(15);

	//Reset EN
	GPIOB->BSRR=EN<<16; //reset-0
	delayMS(15);
}

void LCD_init(void){
	unsigned char i=0;
	GPIO_init();
	LCD_Command(0x28); //to set 8 bit data mode
	delayMS(15);
	LCD_Command(0x0C); //move the curser right
	delayMS(15);
	LCD_Command(0x06);
	delayMS(15);
	LCD_Command(0x01); //Clear screen move cursor home
	delayMS(15);
	LCD_Command(0x80); //Turn display
	delayMS(15);
	while(message[i]!='\0'){
		LCD_data(message[i]);
		i++;
	}
	delayMS(30);
}

void delayMS(int delay){
	int i;
	for(;delay>0;delay--){
		for(i=0;i<3195;i++){

		}
	}
}
