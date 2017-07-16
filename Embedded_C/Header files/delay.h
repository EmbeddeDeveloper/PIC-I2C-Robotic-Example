/*--------------------------------------------------------------------------
delay.H

Header file for Philips 8xC31/51, 80C51Fx, 80C51Rx+, 80C51Rx2
Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __delay_H__
#define __delay_H__

void delay(unsigned int time);
//---------------------------------
void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}
//---------------------------------
#endif
