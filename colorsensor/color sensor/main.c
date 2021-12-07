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
	int succ2;
	int succ;
	int actual[5];
	int high[4];
	int low[4];
	int i;
	int j;
	float avg;
    DDRC = 0xF0;
	PORTC = 0x3F;
	uart_init();
	io_redirect();
	i2c_init();
	i2c_start((0x29<<1)+I2C_WRITE);
	i2c_write(0x80+0x01);
	i2c_write(0xFF);
	i2c_start((0x29<<1)+I2C_WRITE);
	i2c_write(0x80+0x0F);
	i2c_write(0x02);
	i2c_start((0x29<<1)+I2C_WRITE);
	i2c_write(0x80+0x00);
	i2c_write(0x01);
	_delay_ms(3);
	i2c_start((0x29<<1)+I2C_WRITE);
	i2c_write(0x80+0x00);
	i2c_write(0x03);
	_delay_ms(5);
	i2c_start((0x29<<1)+I2C_WRITE);
	i2c_write(0xA0+0x16);
	i2c_start((0x29<<1)+I2C_READ);
	succ = i2c_readAck();
	succ2 = i2c_readAck();
	for (i=0; i<5; i++)
	{
		actual[i] = ((succ2<<8) | succ);
	}
	avg = ((succ2<<8) | succ);
	while (1)
	{
		_delay_ms(5);
		i2c_start((0x29<<1)+I2C_WRITE);
		i2c_write(0xA0+0x16);
		i2c_start((0x29<<1)+I2C_READ);
		succ = i2c_readAck();
		succ2 = i2c_readAck();
		printf("Red: %d\n", ((succ2<<8) | succ));
		if (((succ2<<8) | succ) < avg - 50)
		{
			for (i=0; i<5; i++)
			{
				if (i=4)
				{
					for (j=0; j<4; j++)
					{
						actual[j]=low[j];
					}
					actual[4]=((succ2<<8) | succ)
				}
				else
				{
					if (low[i] = 0)
					{
						low[i] = ((succ2<<8) | succ);
						i = 5;
					}
				}
			}
		}
	}
}

