/*
 * color sensor.c
 *
 * Created: 01-11-2021 08:39:47
 * Author : ttoft
 */ 
#define F_CPU 16E6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "usart.h"
#include "i2cmaster.h"


int main(void)
{
	char str[5];
	int succ;
    DDRC = 0xF0;
	PORTC = 0x3F;
	uart_init();
	io_redirect();
	while (1) 
    {
		printf("hello!\n");
		scanf("%s", &str);
		printf("%s\n", str);
		_delay_ms(2000);
    }
}

